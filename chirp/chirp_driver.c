#define CHIRP_I2C_ADDR 0x20 // chirp I2C address
#define CHIRP_I2C_CAPA 0 // value for reading capacitance sensor
#define CHIRP_I2C_TEMP 5 // value for reading temperature sensor

const int CHIRP_HUM_BOTTOM = 297;
const int CHIRP_HUM_TOP = 765;

void chirp_setup() {
    pinMode(ENABLE_STEP_UP_PIN, OUTPUT);
}

void chirp_start() {
    // power on chirp
    digitalWrite(ENABLE_STEP_UP_PIN, ENABLE_STEP_UP_ON);
    delay(200);
    // initialize I2C communication
    Wire.begin();
}

void chirp_stop() {
    // end I2C communication
    Wire.end();
    // power off chirp
    digitalWrite(ENABLE_STEP_UP_PIN, ENABLE_STEP_UP_OFF);
}

unsigned int chirp_read(int value) {
    Wire.beginTransmission(CHIRP_I2C_ADDR); // start comm with chirp
    Wire.write(value); // write which sensor to read
    Wire.endTransmission();

    delay(20); // wait for measurement

    Wire.requestFrom(CHIRP_I2C_ADDR,2); // store 2 byte in Wire buffer
    unsigned int t = Wire.read() << 8; // read first byte and move to msb
    return t | Wire.read(); // read & add second byte (lsb)
}

int hum_to_percent(unsigned int value) {
    return 100/(CHIRP_HUM_TOP-CHIRP_HUM_BOTTOM)*(value-CHIRP_HUM_BOTTOM);
}