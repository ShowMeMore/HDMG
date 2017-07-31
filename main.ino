#include <Wire.h>

/* globals */
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
        Serial.println("Enter Connect Mode (m)");
      } else {
        state = SLEEP;
        Serial.println("Enter Sleep Mode (m)");
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
        Serial.println("Enter Send Mode (c)");
      } else {
        if (!plantState) {
          if (n>0) {
            n--;
          } else {
            sFlag = false;
            state = SLEEP;
            Serial.println("Enter Sleep Mode (c)");
          }
        } else {
          sFlag = false;
          state = SLEEP;
          Serial.println("Enter Sleep Mode (c)");
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
      Serial.println("Enter Sleep Mode (s)");
    }
    break;

    //sleep
    case 4: {
      Serial.println("sleeping...");
      led_on(LED_PIN_BUILTIN);
      if (mFlag) {
        state = MEASURE;
        led_off(LED_PIN_BUILTIN);
        Serial.println("Enter Measure Mode (s)");
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