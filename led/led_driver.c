#include "led_driver.h"

void led_setup() {
    // initialize LED communication
    // initialize digital pin LED_BUILTIN as an output.
    pinMode(LED_ADDR_BUILTIN, OUTPUT);
    led_status = false;
}

// Turn LED on
void led_on() {
    digitalWrite(LED_ADDR_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
    led_status = true;
}

// Turn LED off
void led_off() {
    digitalWrite(LED_ADDR_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
    led_status = false;
}

// Toggle LED
void led_toggle() {
    if (led_status) {
        led_off();
    }
    else {
        led_on();
    }
}

// LED blinking with on_duration and off_duration
void led_blink(int on_duration, int off_duration) {
    led_on();
    delay(on_duration);
    led_off();
    delay(off_duration);
}