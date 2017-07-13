#include <Wire.h>

#include "hardware/hardware.h"
#include "chirp/chirp_driver.c"
#include "led/led_driver.c"

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize LED
  led_setup(LED_PIN);
  chirp_setup();
  // initialize serial monitor with baude rate
  Serial.begin(9600);
}

// the loop function runs over and over again forever
void loop() {

  led_blink(LED_PIN, 500, 1000);    // turn the LED on
  
  chirp_start();
  Serial.println(chirp_read(CHIRP_I2C_CAPA));
  chirp_stop();

  //led_toggle(LED_PIN_CURRENT);
  //delay(500);

  //Serial.println(chirp_read(CHIRP_I2C_CAPA));
  //Serial.println(chirp_read(CHIRP_I2C_TEMP));
  //led_blink(2000,500);
  //Serial.println(chirp_read(CHIRP_I2C_CAPA));

}