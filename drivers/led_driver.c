boolean led_status; // to get the status ot the LED: on=true / off=false

void led_setup(int pin) {
    // initialize LED communication
    // initialize digital pin LED_BUILTIN as an output.
    debug_msg("led_driver: Setup LED... ", DEBUG_LED);
    pinMode(pin, OUTPUT);
    digitalWrite(pin, LED_OFF);
    led_status = false;
    debug_msg_ln("DONE", DEBUG_LED);
}

// Turn LED on
void led_on(int pin) {
    debug_msg("led_driver: Turn LED on... ", DEBUG_LED);
    //pinMode(pin, OUTPUT);
    digitalWrite(pin, LED_ON);   // turn the LED on (HIGH is the voltage level)
    led_status = true;
    debug_msg_ln("DONE", DEBUG_LED);
}

// Turn LED off
void led_off(int pin) {
    debug_msg("led_driver: Turn LED off... ", DEBUG_LED);
    digitalWrite(pin, LED_OFF);    // turn the LED off by making the voltage LOW
    //pinMode(pin, INPUT);
    led_status = false;
    debug_msg_ln("DONE", DEBUG_LED);
}

// Toggle LED
void led_toggle(int pin) {
    debug_msg("led_driver: Toggle LED... ", DEBUG_LED);
    if (led_status) {
        led_off(pin);
        ledBlinkTicker.detach();
        ledBlinkTicker.attach(ledBlinkTicker_handle, TIMER_VALUE_LED_BLINK_OFF);
        debug_msg_ln("led_driver: set led timer to on", DEBUG_LED);
    }
    else {
        led_on(pin);
        ledBlinkTicker.detach();
        ledBlinkTicker.attach(ledBlinkTicker_handle, TIMER_VALUE_LED_BLINK_ON);
        debug_msg_ln("led_driver: set led timer to off", DEBUG_LED);
    }
    debug_msg_ln("DONE", DEBUG_LED);
}

// LED blinking with on_duration and off_duration
/* this routine should only be used for development - highly energyineffiecient
void led_blink(int pin, int on_duration, int off_duration) {
    debug_msg("led_driver: Blink LED... ", DEBUG_LED);
    led_on(pin);
    delay(on_duration);
    led_off(pin);
    delay(off_duration);
    debug_msg_ln("DONE", DEBUG_LED);
}*/

// LED blinking with measured value: more thirsty --> longer blink
void led_valueblink(int pin, int total_duration, int value) {
    debug_msg("led_driver: Blink LED with value... ", DEBUG_LED);
    int max_on_duration = total_duration/2;
    if (value <= HUM_ALARM_VALUE){
        int on_duration = max_on_duration/HUM_ALARM_VALUE*(HUM_ALARM_VALUE-value);
        int off_duration = total_duration-on_duration;
        led_on(pin);
        delay(on_duration);
        led_off(pin);
        delay(off_duration);
        debug_msg_ln("DONE", DEBUG_LED);
    }
    debug_msg_ln("DONE (no blink)", DEBUG_LED);
}