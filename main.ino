// define the states of the statemachine
#define MEASURE 1
#define CONNECT 2
#define SEND 3
#define SLEEP 4
// define the timer values in seconds
#define TIMER_VALUE_MEASURE 3600 // do measurement every 2h: 7200
#define TIMER_VALUE_LED_BLINK 1 // blink for 1s when thirsty
#define TIMER_VALUE_LED_STOP 7200 // stop blinking (thirsty) after 2h: 7200
#define TIMER_VALUE_SEND 360 // send data every 6h: 21600
// define threshold to give water
#define HUM_ALARM_VALUE 50 // for testing purpose only, be sure led will blink, was 15
// define the states of the plant
#define PLANT_OK true
#define PLANT_THIRSTY false
// define off/on fraction
#define LED_BLINK_FRAC 4 // 4x longer off than on

// globals, before includes!
int state = MEASURE;  // current state, enum {MEASURE, CONNECT, SEND, SLEEP}
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
  //ledBlinkTicker.attach(ledBlinkTicker_handle, TIMER_VALUE_LED_BLINK);
  // ticker to stop LED blinking
  //ledStopTicker.attach(ledStopTicker_handle, TIMER_VALUE_LED_STOP);
  // ticker to send values --> implement later



  sendTicker.attach(sendTicker_handle, TIMER_VALUE_SEND);
}

void loop() {
/*  // LED Test & transisto
  chirp_start();
  led_on(LED_PIN);
  delay(200);
  debug_msg_ln(chirp_read(CHIRP_I2C_CAPA),DEBUG_CHIRP);
  delay(1000);
  chirp_stop();
  led_off(LED_PIN);
  delay(1000);*/
  // Turn on serial monitor only if needed, should be enabled in ISRs
//  debug_setup();

  switch (state) {

    // measure state: doint measurement
    case MEASURE: {
      // do measurement
      humidity = chirp_read_stable(); // do new measurement
      debug_msg_ln(humidity, DEBUG_VALUES);
      writeMeasureBuffer(humidity); // write new measured value to buffer
      measureFlag = false;
      // set plantState
      if (humidity < HUM_ALARM_VALUE)
      {
        plantState = PLANT_THIRSTY;
        ledFlag = true;
        ledBlinkTicker.attach(ledBlinkTicker_handle, TIMER_VALUE_LED_BLINK);
      } else {
        plantState = PLANT_OK;
        ledFlag = false;
        led_off(LED_PIN);
        ledBlinkTicker.detach();
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
        sendFlag = false; // clear flag after successful data transmission
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
      else if (sendFlag) {
        state = SEND;
        debug_msg_ln("Leave Sleep Mode - Enter Send Mode", DEBUG_STATE);
      }
      else if (ledFlag) {
        led_toggle(LED_PIN);
        debug_msg_ln("Too Dry - Need Water!!!", DEBUG_STATE);
        ledFlag = false;
      }
      else{
        // go to sleep mode
        debug_stop();
        __WFI();
      }
    }
    break;

  }
}