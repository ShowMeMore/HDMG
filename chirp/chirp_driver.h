#define ADDR 0x20 // chirp I2C address
#define CAPA 0 // value for reading capacitance sensor
#define TEMP 5 // value for reading temperature sensor

// setup chirp (I2C comm)
void chirp_setup();

// return sensor value
unsigned int chirp_read(int);