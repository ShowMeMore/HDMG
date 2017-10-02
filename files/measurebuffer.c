void clearMeasureBuffer(void){
  debug_msg("measurebuffer: Clear MeasureBuffer... ", DEBUG_STATE);
  for (int i = 0; i < 12; ++i) {
    MeasureBuffer[i] = 0;
  }
  debug_msg_ln("DONE", DEBUG_STATE);
}

void writeMeasureBuffer(int value){
  debug_msg("measurebuffer: Write to MeasureBuffer... ", DEBUG_STATE);
  boolean writeStatus = false;
  for (int i = 0; i < 12; ++i) {
    if (!writeStatus && (MeasureBuffer[i] == 0)){
      MeasureBuffer[i] = value;
      writeStatus = true;
    }
  }
  if (writeStatus){
    debug_msg_ln("DONE", DEBUG_STATE);
  }else{
    debug_msg_ln("ERROR", DEBUG_STATE);
  }
}

void readMeasureBuffer(void){
  debug_msg_ln("measurebuffer: Read MeasureBuffer... ", DEBUG_STATE);
  for (int i = 0; i < 12; ++i) {
    debug_msg(MeasureBuffer[i], DEBUG_STATE);
    debug_msg(" / ", DEBUG_STATE);
  }
  //debug_msg_ln("DONE", DEBUG_STATE);
  debug_msg_ln("", DEBUG_STATE);
  debug_msg_ln("measurebuffer: Read MeasureBuffer... DONE", DEBUG_STATE);
}