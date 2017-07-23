// define different states
const int MEASURE = 1;
const int CONNECT = 2;
const int SEND = 3;
const int SLEEP = 4;

void mTicker_handle(void) {
  mFlag = true; //wake up to measure
}
void sTicker_handle(void) {
  sFlag = true; //wake up to send
}
void lTicker_handle(void) {
  lFlag = true; //wake up to blink LED
}