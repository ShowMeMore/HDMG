// define the states of the statemachine
#define MEASURE 1
#define CONNECT 2
#define SEND 3
#define SLEEP 4
// define the timer values in seconds
#define TIMER_VALUE_MEASURE 10 // do measurement every hour: 3600
#define TIMER_VALUE_LED 3
#define TIMER_VALUE_SEND 60 // send data every 6 hour: 21600
// define threshold to give water
#define HUM_ALARM_VALUE 50
//define the states of the plant
#define PLANT_OK true
#define PLANT_THIRSTY false

// globals, before includes
int state = SLEEP;  // enum {MEASURE, CONNECT, SEND, SLEEP}
boolean plantState = PLANT_OK; // enum {PLANT_OK, PLANT_THIRSTY}
byte n; // 8 bit unsigned integer
int MeasureBuffer[12]; // store the measure values for 1 day (each 2 hours)
boolean  measureFlag, sendFlag, ledFlag = false;
Ticker measureTicker, sendTicker, ledTicker;

#include <Wire.h>
#include "files/debug.c"
#include "files/statemachine.c"
#include "files/measurebuffer.c"
#include "drivers/hardware.h"
#include "drivers/chirp_driver.c"
#include "drivers/led_driver.c"

void setup() {
  // initialize serial monitor with baude rate 9600
  debug_setup();
  // initialize LED
  led_setup(LED_PIN);
  // initialize chirp
  chirp_setup();
  // ticker to start measurement
  measureTicker.attach(measureTicker_handle, TIMER_VALUE_MEASURE);
  //ticker for led
  ledTicker.attach(ledTicker_handle, TIMER_VALUE_LED);
  // ticker to send --> implement later
  sendTicker.attach(sendTicker_handle, TIMER_VALUE_SEND);
}

void loop() {
  switch (state) {

    // measure state
    case MEASURE: {
      // LED indicates measurement
      led_on(LED_PIN);
      // do measurement
      debug_msg_ln(chirp_read_value(CHIRP_I2C_CAPA), DEBUG_STATE); //
      int humidity = chirp_read_stable();
      debug_msg_ln(humidity, DEBUG_STATE);
      writeMeasureBuffer(humidity);
      // set plantState
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
      // check plantState for LED
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
      led_off(LED_PIN);
    }
    break;

    // connect state --> implement later
    case CONNECT: {
      // do: setup ble adertising
      // wait?
      if (true) { //bleconnected
        state = SEND;
        debug_msg_ln("Leave Connect Mode - Enter Send Mode", DEBUG_STATE);
      } else {
        if (n>0) {
          n--;
        } else {
          sendFlag = false;
          state = SLEEP;
          debug_msg_ln("Connection failed", DEBUG_STATE);
          debug_msg_ln("Leave Connect Mode - Enter Sleep Mode", DEBUG_STATE);
        }
      }
    }
    break;

    // send state --> implement later
    case SEND: {
      // do: send data
      readMeasureBuffer();
      if (true) { // data sent
        // do: close ble connection
        // do: failure exception
        //clearMeasureBuffer();
        state = SLEEP;
        debug_msg_ln("Leave Send Mode - Enter Sleep Mode", DEBUG_STATE);
      } else {

      }      
    }
    break;

    // sleep state
    case SLEEP: {
      led_on(LED_PIN_BUILTIN); // use builtin LED to indicate sleep mode
      if (measureFlag) {
        state = MEASURE;
        debug_msg_ln("Leave Sleep Mode - Enter Measure Mode", DEBUG_STATE);
        led_off(LED_PIN_BUILTIN);
      }
      else if (ledFlag) {
        led_blink(LED_PIN,200,0);
        debug_msg_ln("Too Dry - Need Water!!!", DEBUG_STATE);
        ledFlag = false;
      }
      // do: setup sleep mode
    }
    break;

  }

}