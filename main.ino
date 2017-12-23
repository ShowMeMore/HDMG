// define the states of the statemachine
#define MEASURE 1
#define CONNECT 2
#define SEND 3
#define SLEEP 4
// define the timer values in seconds
#define TIMER_VALUE_MEASURE 60 // do measurement every 2h: 7200
#define TIMER_VALUE_LED_BLINK 1 // blink every 3s when thirsty: 3
#define TIMER_VALUE_LED_STOP 7200 // stop blinking (thirsty) after 2h: 7200
#define TIMER_VALUE_SEND 180 // send data every 6h: 21600
// define threshold to give water
#define HUM_ALARM_VALUE 50
//define the states of the plant
#define PLANT_OK true
#define PLANT_THIRSTY false

// globals, before includes!
int state = SLEEP;  // current state, enum {MEASURE, CONNECT, SEND, SLEEP}
int humidity; // value of latest humidity measurement
boolean plantState = PLANT_OK; // current plant state, enum {PLANT_OK, PLANT_THIRSTY}
byte n; // 8 bit unsigned integer
int MeasureBuffer[24]; // store the measured values in a buffer
boolean  measureFlag, sendFlag, ledFlag = false;
Ticker measureTicker, ledStopTicker, ledBlinkTicker, sendTicker;

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
  // initialize buffer
  clearMeasureBuffer();
  // ticker to start measurement
  measureTicker.attach(measureTicker_handle, TIMER_VALUE_MEASURE);
  // ticker for LED blinking interval
  ledBlinkTicker.attach(ledBlinkTicker_handle, TIMER_VALUE_LED_BLINK);
  // ticker to stop LED blinking
  //ledStopTicker.attach(ledStopTicker_handle, TIMER_VALUE_LED_STOP);
  // ticker to send values --> implement later
  sendTicker.attach(sendTicker_handle, TIMER_VALUE_SEND);
}

void loop() {
  switch (state) {

    // measure state: doint measurement
    case MEASURE: {
      //led_on(LED_PIN); // LED indicates measurement
      // do measurement
      humidity = chirp_read_stable(); // do new measurement
      debug_msg_ln(humidity, DEBUG_VALUES);
      writeMeasureBuffer(humidity); // write new measured value to buffer
      // set plantState
      if (humidity < HUM_ALARM_VALUE)
      {
        plantState = PLANT_THIRSTY;
        ledFlag = true;
        ledBlinkTicker.attach(ledBlinkTicker_handle, TIMER_VALUE_LED_BLINK);
      }else{
        plantState = PLANT_OK;
        led_off(LED_PIN);
        ledFlag = false;
        ledBlinkTicker.detach();
      }
      measureFlag = false;
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
      if (measureFlag) {
        state = MEASURE;
        debug_msg_ln("Leave Sleep Mode - Enter Measure Mode", DEBUG_STATE);
      }
      else if (ledFlag) {
        //led_blink(LED_PIN,200,0);
        //led_valueblink(LED_PIN, 2000, humidity);
        led_toggle(LED_PIN);
        debug_msg_ln("Too Dry - Need Water!!!", DEBUG_STATE);
        ledFlag = false;
      }
      else{
        __WFI();
      }
    }
    break;

  }

}