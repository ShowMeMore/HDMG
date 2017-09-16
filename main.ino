#define PLANT_OK true
#define PLANT_THIRSTY false

#define MEASURE 1
#define CONNECT 2
#define SEND 3
#define SLEEP 4

#define HUM_ALARM_VALUE 50

#include <Wire.h>

// globals
int state = SLEEP;
boolean plantState = PLANT_OK; // enum {PLANT_OK, PLANT_THIRSTY}
byte n; // 8 bit unsigned integer
boolean  measureFlag, sendFlag, ledFlag = false;
Ticker measureTicker, sendTicker, ledTicker;

#include "files/debug.c"
#include "files/statemachine.c"
#include "drivers/hardware.h"
#include "drivers/led_driver.c"
#include "drivers/chirp_driver.c"

void setup() {
  // initialize serial monitor with baude rate
  debug_setup();
  // initialize LED
  led_setup(LED_PIN);
  // initialize chirp
  chirp_setup();
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
    case MEASURE: {
      //LED indicates measurement
      led_blink(LED_PIN,2000,0);
      // do measurement
      debug_msg_ln(chirp_read_value(CHIRP_I2C_CAPA), DEBUG_STATE); //
      float humidity = chirp_read_stable();
      debug_msg_ln(humidity, DEBUG_STATE);
      if (humidity < HUM_ALARM_VALUE)
      {
        plantState = PLANT_THIRSTY;
        ledFlag = true;
        ledTicker.attach(ledTicker_handle, 3);
      }else{
        plantState = PLANT_OK;
        ledFlag = false;
        ledTicker.detach();
      }
      measureFlag = false;

      //check plantState for LED
      if (plantState == PLANT_THIRSTY) {
        // do Set Led Timer
      } else {
        // do Clear Led Timer
      }

      // determine transition & prep
      if (sendFlag) {
        state = CONNECT;
        n = 7;
        debug_msg_ln("Leave Measure Mode - Enter Connect Mode", DEBUG_STATE);
      } else {
        state = SLEEP;
        debug_msg_ln("Leave Measure Mode - Enter Sleep Mode", DEBUG_STATE);
      }
    }
    break;

    // connect --> implement later
    case CONNECT: {
      // do
      // setup ble adertising
      // wait?
      
      // determine transition & prep
      if (true) { //bleconnected
        state = SEND;
        debug_msg_ln("Leave Connect Mode - Enter Send Mode", DEBUG_STATE);
      } 
      else {
        if (!plantState) {
          if (n>0) {
            n--;
          } 
          else {
            sendFlag = false;
            state = SLEEP;
            debug_msg_ln("Connection failed", DEBUG_STATE);
            debug_msg_ln("Leave Connect Mode - Enter Sleep Mode", DEBUG_STATE);
          }
        } else {
          sendFlag = false;
          state = SLEEP;
          debug_msg_ln("Leave Connect Mode - Enter Sleep Mode", DEBUG_STATE);
        }
      }
    }
    break;

    //send --> implement later
    case SEND: {
      // do
      // send data
      // clear data
      // close ble connection
      // failure exception
      
      // determine transition & prep
      state = SLEEP;
      debug_msg_ln("Leave Send Mode - Enter Sleep Mode", DEBUG_STATE);
    }
    break;

    //sleep
    case SLEEP: {
      led_on(LED_PIN_BUILTIN);
      if (measureFlag) {
        state = MEASURE;
        led_off(LED_PIN_BUILTIN);
        debug_msg_ln("Leave Sleep Mode - Enter Measure Mode", DEBUG_STATE);
      }
      else if (ledFlag) {
        led_blink(LED_PIN,200,0);
        debug_msg_ln("Too Dry - Need Water!!!", DEBUG_STATE);
        ledFlag = false;
      }
      // do  setup sleep mode
      
      // determine transition & prep
      //Switch state {
        //Case: sleep {
          // go to sleep
        //}
      //}
    }
    break;
  }

}