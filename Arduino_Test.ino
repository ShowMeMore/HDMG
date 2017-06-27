#include <Wire.h>
#include "chirp/chirp_driver.c"

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  // initialize chirp
  chirp_setup();
  // initialize serial monitor with baude rate
  Serial.begin(9600);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(500);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(500);                       // wait for a second

  Serial.print(chirp_read(CAPA));
  Serial.print(", ");
  Serial.println(chirp_read(TEMP));
}