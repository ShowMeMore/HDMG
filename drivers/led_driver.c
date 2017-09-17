boolean led_status;

void led_setup(int pin) {
    // initialize LED communication
    // initialize digital pin LED_BUILTIN as an output.
    pinMode(pin, OUTPUT);
    led_status = false;
    debug_msg_ln("led_driver: setup led", DEBUG_LED);
}

// Turn LED on
void led_on(int pin) {
    digitalWrite(pin, ENABLE_LED_ON);   // turn the LED on (HIGH is the voltage level)
    led_status = true;
    debug_msg_ln("led_driver: led turned on", DEBUG_LED);
}

// Turn LED off
void led_off(int pin) {
    digitalWrite(pin, ENABLE_LED_OFF);    // turn the LED off by making the voltage LOW
    led_status = false;
    debug_msg_ln("led_driver: led turned off", DEBUG_LED);
}

// Toggle LED
void led_toggle(int pin) {
    if (led_status) {
        led_off(pin);
        debug_msg_ln("led_driver: led toggled off", DEBUG_LED);
    }
    else {
        led_on(pin);
        debug_msg_ln("led_driver: led toggled on", DEBUG_LED);
    }
}

// LED blinking with on_duration and off_duration
void led_blink(int pin, int on_duration, int off_duration) {
    led_on(pin);
    delay(on_duration);
    led_off(pin);
    delay(off_duration);
    debug_msg_ln("led_driver: led blinked", DEBUG_LED);
}