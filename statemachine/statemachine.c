#include "statemachine.h"

void measureTicker_handle(void) {
  mFlag = true; //wake up to measure
}
void sendTicker_handle(void) {
  sFlag = true; //wake up to send
}
void ledTicker_handle(void) {
  lFlag = true; //wake up to blink LED
}