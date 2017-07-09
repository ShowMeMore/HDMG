#include <Wire.h>
#include "chirp/chirp_driver.c"
#include "led/led_driver.c"
#include "statemachine/statemachine.c"

/* globals */
int state = 4;
boolean plantState = true; // ok=true, nok=false
byte n; // 8 bit unsigned integer
boolean  mFlag, sFlag, lFlag = false;
Ticker mTicker, sTicker, lTicker;

void setup() {
  // initialize LED
  led_setup();
  // initialize chirp
  chirp_setup();
  // initialize serial monitor with baude rate
  Serial.begin(9600);
  // creat two task, one 1s and the other 2s
  mTicker.attach_us(mTicker_handle, 1000000);
  sTicker.attach(sTicker_handle, 2);
}

void loop() {
  switch (state) {

    case MEASURE: {
      mFlag = false;
      // measure…
      if (!plantState) {
        // Set Led Timer
      } else {
        // Clear Led Timer
      }
      /* determine transition & prep */
      if (sFlag) {
        state = CONNECT;
        n = 7;
      } else {
        state = SLEEP;
      }
    }
    break;

    case CONNECT: {
      /* do */
      // setup ble adertising
      // wait?
      
      /* determine transition & prep */
      if (true) { //bleconnected
        state = SEND;
      } else {
        if (!plantState) {
          if (n>0) {
            n--;
          } else {
            sFlag = false;
            state = SLEEP;
          }
        } else {
          sFlag = false;
          state = SLEEP;
        }
      }
    }
    break;

    case SEND: {
      /* do */
      // send data
      // clear data
      // close ble connection
      // failure exception
      
      /* determine transition & prep */
      state = SLEEP;
    }
    break;

    case SLEEP: {
      /* do */
      if (mFlag) state = MEASURE;
      // setup sleep mode
      
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