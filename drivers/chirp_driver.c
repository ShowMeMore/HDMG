#define CHIRP_I2C_ADDR 0x20 // chirp I2C address
#define CHIRP_I2C_CAPA 0 // value for reading capacitance sensor
#define CHIRP_I2C_TEMP 5 // value for reading temperature sensor
#define CHIRP_I2C_SLEEP 8 // value for putting chirp in sleep mode
#define CHIRP_I2C_RESET 6 // value for resetting chirp

#define NBR_PRETESTS 3 // number of tests befor averaging sensor value
#define NBR_TESTS 32 // number of tests for averaging sensor value
#define NBR_MAX_ERRORS 32 // max number of failed tests in stable 

#define CHIRP_HUM_BOTTOM 290 // min value for moisture sensor
#define CHIRP_HUM_TOP 765 // max value for moisture sensor


void chirp_setup() {
    pinMode(ENABLE_STEP_UP_PIN, OUTPUT);
    digitalWrite(ENABLE_STEP_UP_PIN, ENABLE_STEP_UP_OFF);
}

void chirp_start() {
    // power on chirp
    debug_msg("chirp_driver: Powering on step up... ", DEBUG_CHIRP);
    digitalWrite(ENABLE_STEP_UP_PIN, ENABLE_STEP_UP_ON);
    debug_msg_ln("DONE", DEBUG_CHIRP);
    delay(500);
    // initialize I2C communication
    debug_msg("chirp_driver: Starting Wire... ", DEBUG_CHIRP);
    Wire.begin();
    // reset chirp
    Wire.beginTransmission(CHIRP_I2C_ADDR);
    Wire.write(CHIRP_I2C_RESET);
    Wire.endTransmission();
    delay(100);
    debug_msg_ln("DONE", DEBUG_CHIRP);
}

void chirp_stop() {
    // put Chirp to sleep mode (so that thyristor shuts down)
    Wire.beginTransmission(CHIRP_I2C_ADDR);
    Wire.write(CHIRP_I2C_SLEEP); 
    Wire.endTransmission();
    // end I2C communication
    Wire.end();
    // power off chirp
    digitalWrite(ENABLE_STEP_UP_PIN, ENABLE_STEP_UP_OFF);
    debug_msg_ln("chirp_driver: Wire and power turned off", DEBUG_CHIRP);
}

unsigned int chirp_read(int sensor) {
    // read out chirp sensor
    Wire.beginTransmission(CHIRP_I2C_ADDR); // start comm with chirp
    Wire.write(sensor); // write which sensor to read
    Wire.endTransmission();

    delay(20); // wait for measurement

    Wire.requestFrom(CHIRP_I2C_ADDR,2); // store 2 byte in Wire buffer
    unsigned int t = Wire.read() << 8; // read first byte and move to msb
    return t | Wire.read(); // read & add second byte (lsb)
}

unsigned int chirp_read_value(int sensor) {
    chirp_start();
    unsigned int result = chirp_read(sensor);
    chirp_stop();
    return result;
}

int chirp_to_percent(unsigned int value) {
    int val = (float)100/(CHIRP_HUM_TOP-CHIRP_HUM_BOTTOM)*(value-CHIRP_HUM_BOTTOM);
    return val;
}

// averaged sensor value of moisture sensor
int chirp_read_stable() {
    unsigned int sum = 0;
    unsigned int value;
    chirp_start();
    // read sensor values without using them
    for (char i=0; i<NBR_PRETESTS; i++) {
        chirp_read(CHIRP_I2C_CAPA);
    }
    // sum up sensor values for averaging
    char i = NBR_TESTS;
    char count_errors = 0;
    while (i > 0) {
        value = chirp_read(CHIRP_I2C_CAPA);
        // catch if error occurs when reading sensor value
        if ((value >= CHIRP_HUM_BOTTOM) && (value <= CHIRP_HUM_TOP)) {
            sum += value;
            i--;
        } else {
            count_errors++;
            if (count_errors > NBR_MAX_ERRORS) {
                // too many error value sensor reads
                return 0;
            }
        }
    }
    chirp_stop();
    // (unsigned int) sum = [0 65535]
    // max sensor value: 765
    // max nbr of tests: 65535/765 = 85
    return chirp_to_percent(sum / NBR_TESTS);
}
