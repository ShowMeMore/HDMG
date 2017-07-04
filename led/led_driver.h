#define LED_ADDR D13 // pin of LED pin
#define LED_ADDR_BUILTIN D13 // pin of BLENano builtin led

boolean led_status;

// setup LED
void led_setup();

// turn LED on
void led_on();

// turn LED off
void led_off();

// toggle LED
void led_toggle();

// blink LED with on-duration off-duration
void led_blink(int, int);