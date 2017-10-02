void measureTicker_handle(void) {
  debug_msg("statemachine: Set measureFlag to true... ", DEBUG_STATE);
  measureFlag = true; // wake up to measure
  debug_msg_ln("DONE", DEBUG_STATE);
}

void sendTicker_handle(void) {
  debug_msg("statemachine: Set sendFlag to true... ", DEBUG_STATE);
  sendFlag = true; // wake up to send
  debug_msg_ln("DONE", DEBUG_STATE);
}

void ledTicker_handle(void) {
  debug_msg("statemachine: Set ledFlag to true... ", DEBUG_STATE);
  ledFlag = true; // wake up to blink LED
  debug_msg_ln("DONE", DEBUG_STATE);
}