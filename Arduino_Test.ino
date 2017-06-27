#include <Wire.h>

#define CAPA 0
#define TEMP 5

// I2C address of Chirp
int addr = 0x20;

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  // initialize i2c communication
  Wire.begin();
  // initialize serial monitor with baude rate
  Serial.begin(9600);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(500);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(500);                       // wait for a second

  // read 16bit register of chirp capacitance
  /* Chirp read procedure:
  - write "sensor value"
  - wait for measurement -> delay(20)
  - read number of bytes
  sensor; sensor value; #bytes
  capacitance; 0; 2
  temperature; 5; 2
  light; 3 + 4 (write 2 values!); 2 */
  Wire.beginTransmission(addr);
  Wire.write(CAPA);  
  Wire.endTransmission();
  delay(20);
  Wire.requestFrom(addr,2);

  unsigned int t = Wire.read() << 8;
  t = t | Wire.read();
  Serial.println(t);
}