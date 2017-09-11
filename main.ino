#define PLANT_OK true
#define PLANT_THIRSTY false

#define MEASURE 1
#define CONNECT 2
#define SEND 3
#define SLEEP 4

#define HUM_ALARM_VALUE 50

#include <Wire.h>

/* globals */
int state = SLEEP;
boolean plantState = PLANT_OK; // enum {PLANT_OK, PLANT_THIRSTY}
byte n; // 8 bit unsigned integer
boolean  measureFlag, sendFlag, ledFlag = false;
Ticker measureTicker, sendTicker, ledTicker;

#include "hardware/hardware.h"
#include "led/led_driver.c"
#include "chirp/chirp_driver.c"
#include "statemachine/statemachine.c"

void setup() {
  // initialize serial monitor with baude rate
  Serial.begin(9600);
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
      /* do measurement*/
      chirp_start();
      Serial.println(chirp_read(CHIRP_I2C_CAPA)); //
      float humidity = chirp_read_stable();
      chirp_stop();
      Serial.println(humidity);
      if (humidity < HUM_ALARM_VALUE)
      {
        plantState = PLANT_THIRSTY;
        lFlag = true;
        ledTicker.attach(ledTicker_handle, 3);
      }else{
        plantState = PLANT_OK;
        lFlag = false;
        ledTicker.detach();
      }
      mFlag = false;

      //check plantState for LED
      if (plantState == PLANT_THIRSTY) {
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
    case CONNECT: {
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
            Serial.println("Connection failed");
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
    case SEND: {
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
    case SLEEP: {
      led_on(LED_PIN_BUILTIN);
      if (mFlag) {
        state = MEASURE;
        led_off(LED_PIN_BUILTIN);
        Serial.println("Leave Sleep Mode - Enter Measure Mode");
      }
      if (lFlag) {
        led_blink(LED_PIN,200,0);
        Serial.println("Too Dry - Need Water!!! ");
        lFlag = false;
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