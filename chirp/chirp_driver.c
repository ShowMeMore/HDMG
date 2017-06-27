#include "chirp_driver.h"

void chirp_setup() {
    // initialize I2C communication
    Wire.begin();
}

unsigned int chirp_read(int val) {
    Wire.beginTransmission(ADDR); // start comm with chirp
    Wire.write(val); // write which sensor to read
    Wire.endTransmission();

    delay(20); // wait for measurement

    Wire.requestFrom(ADDR,2); // store 2 byte in Wire buffer
    unsigned int t = Wire.read() << 8; // read first byte and move to msb
    return t | Wire.read(); // read & add second byte (lsb)
}