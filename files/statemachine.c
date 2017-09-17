void measureTicker_handle(void) {
  measureFlag = true; // wake up to measure
  debug_msg_ln("statemachine: measureFlag set to true", DEBUG_STATE);
}
void connectTicker_handle(void) {
  connectFlag = true; // wake up to connect
  debug_msg_ln("statemachine: connectFlag set to true", DEBUG_STATE);  
}
void sendTicker_handle(void) {
  sendFlag = true; // wake up to send
  debug_msg_ln("statemachine: sendFlag set to true", DEBUG_STATE);
}
void ledTicker_handle(void) {
  ledFlag = true; // wake up to blink LED
  debug_msg_ln("statemachine: ledFlag set to true", DEBUG_STATE);
}