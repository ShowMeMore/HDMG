//#define LED_PIN_BUILTIN D13 // pin of BLENano builtin led
//#define LED_PIN D13 // pin of another LED
//#define LED_PIN_CURRENT LED_PIN_BUILTIN // define the current working pin

boolean led_status;

// setup LED
void led_setup(int);

// turn LED on
void led_on(int);

// turn LED off
void led_off(int);

// toggle LED
void led_toggle(int);

// blink LED with on-duration off-duration
void led_blink(int, int, int);