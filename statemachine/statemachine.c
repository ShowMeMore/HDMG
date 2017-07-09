#include "statemachine.h"

void mTicker_handle(void) {
  mFlag = true; //wake up to measure
}
void sTicker_handle(void) {
  sFlag = true; //wake up to send
}
void lTicker_handle(void) {
  lFlag = true; //wake up to blink LED
}