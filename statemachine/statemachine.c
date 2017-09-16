void measureTicker_handle(void) {
  measureFlag = true; //wake up to measure
}
void sendTicker_handle(void) {
  sendFlag = true; //wake up to send
}
void ledTicker_handle(void) {
  ledFlag = true; //wake up to blink LED
}