#include "led_driver.h"

void led_setup(int pin) {
    // initialize LED communication
    // initialize digital pin LED_BUILTIN as an output.
    pinMode(pin, OUTPUT);
    led_status = false;
}

// Turn LED on
void led_on(int pin) {
    digitalWrite(pin, HIGH);   // turn the LED on (HIGH is the voltage level)
    led_status = true;
}

// Turn LED off
void led_off(int pin) {
    digitalWrite(pin, LOW);    // turn the LED off by making the voltage LOW
    led_status = false;
}

// Toggle LED
void led_toggle(int pin) {
    if (led_status) {
        led_off(pin);
    }
    else {
        led_on(pin);
    }
}

// LED blinking with on_duration and off_duration
void led_blink(int pin, int on_duration, int off_duration) {
    led_on(pin);
    delay(on_duration);
    led_off(pin);
    delay(off_duration);
}