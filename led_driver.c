#define LED_PIN_BUILTIN D13 // pin of BLENano builtin led
#define LED_PIN D13 // pin of another LED
#define LED_PIN_CURRENT LED_PIN_BUILTIN // define the current working pin

boolean led_status;

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