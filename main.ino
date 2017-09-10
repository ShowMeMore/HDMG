#include <Wire.h>

/* globals */
const int HUM_ALARM_VALUE = 50;
int state = 4;
boolean plantState = true; // ok=true, nok=false
byte n; // 8 bit unsigned integer
boolean  mFlag, sFlag, lFlag = false;
Ticker measureTicker, sendTicker, ledTicker;

#include "hardware/hardware.h"
#include "led/led_driver.c"
#include "chirp/chirp_driver.c"
#include "statemachine/statemachine.c"

void setup() {
  // initialize LED
  led_setup(LED_PIN);
  // initialize chirp
  chirp_setup();
  // initialize serial monitor with baude rate
  Serial.begin(9600);
  // create two task, one 1s and the other 2s
  //ticker for measure
  measureTicker.attach(measureTicker_handle, 12);
  //ticker to send --> implement later
  //sendTicker.attach(sendTicker_handle, 2);
  //ticker for led
  ledTicker.attach(ledTicker_handle, 3);
}

void loop() {
  switch (state) {

    // measure
    case 1: {
      //LED indicates measurement
      led_blink(LED_PIN,2000,0);
      /* do measurement*/
      chirp_start();
      Serial.println(chirp_read(CHIRP_I2C_CAPA));
      Serial.println(chirp_to_percent(chirp_read(CHIRP_I2C_CAPA)));
      if (chirp_to_percent(chirp_read(CHIRP_I2C_CAPA)) < HUM_ALARM_VALUE)
      {
        plantState = false;
      }else{
        plantState = true;
      }
      chirp_stop();
      mFlag = false;

      //check plantState for LED
      if (!plantState) {
        /* do Set Led Timer */
      } else {
        /* do Clear Led Timer */
      }
      /* determine transition & prep */
      if (sFlag) {
        state = CONNECT;
        n = 7;
        Serial.println("Leave Measure Mode - Enter Connect Mode");
      } else {
        state = SLEEP;
        Serial.println("Leave Measure Mode - Enter Sleep Mode");
      }
    }
    break;

    // connect --> implement later
    case 2: {
      /* do */
      // setup ble adertising
      // wait?
      
      /* determine transition & prep */
      if (true) { //bleconnected
        state = SEND;
        Serial.println("Leave Connect Mode - Enter Send Mode");
      } else {
        if (!plantState) {
          if (n>0) {
            n--;
          } else {
            sFlag = false;
            state = SLEEP;
            Serial.println("Leave Connect Mode - Enter Sleep Mode");
          }
        } else {
          sFlag = false;
          state = SLEEP;
          Serial.println("Leave Connect Mode - Enter Sleep Mode");
        }
      }
    }
    break;

    //send --> implement later
    case 3: {
      /* do */
      // send data
      // clear data
      // close ble connection
      // failure exception
      
      /* determine transition & prep */
      state = SLEEP;
      Serial.println("Leave Send Mode - Enter Sleep Mode");
    }
    break;

    //sleep
    case 4: {
      led_on(LED_PIN_BUILTIN);
      if (mFlag) {
        state = MEASURE;
        led_off(LED_PIN_BUILTIN);
        Serial.println("Leave Sleep Mode - Enter Measure Mode");
      }
      if (!plantState) {
        led_blink(LED_PIN,200,200);
        Serial.print("Too Dry - Need Water!!! ");
      }
      /* do  setup sleep mode*/
      
      /* determine transition & prep */
      //Switch state {
        //Case: sleep {
          // go to sleep
        //}
      //}
    }
    break;
  }

}