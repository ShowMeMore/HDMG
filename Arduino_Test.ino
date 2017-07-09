#include <Wire.h>
#include "chirp/chirp_driver.c"
#include "led/led_driver.c"

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize LED
  led_setup();
  // initialize chirp
  chirp_setup();
  // initialize serial monitor with baude rate
  Serial.begin(9600);
}

// the loop function runs over and over again forever
void loop() {

  //led_on();    // turn the LED on
  //delay(500);      // wait for a second
  //led_off();   // turn the LED off
  //delay(500);      // wait for a second
  
  //led_toggle();
  //delay(500);

  //led_blink(2000,500);

  //Serial.println(chirp_read(CAPA));
  //Serial.println(chirp_read(TEMP));
  //led_blink(2000,500);
  Serial.println(chirp_read(CAPA));

}