void writeMeasureBuffer(int value){
  debug_msg("measurebuffer: Write to MeasureBuffer... ", DEBUG_VALUES);
  boolean writeStatus = false;
  for (int i = 0; i < 24; ++i) {
    if (!writeStatus && (MeasureBuffer[23] == -1)) {
      if (MeasureBuffer[i] == -1) {
        MeasureBuffer[i] = value;
        writeStatus = true;
      }
    } else if (!writeStatus && (MeasureBuffer[23] != -1)) {
        if (i > 0) {
          MeasureBuffer[i-1] = MeasureBuffer[i];
          if (i == 23) {
            MeasureBuffer[i] = value;
            writeStatus = true;
          }
        }
      }
  }
  if (writeStatus){
    debug_msg_ln("DONE", DEBUG_VALUES);
  }else{
    debug_msg_ln("ERROR", DEBUG_VALUES);
  }
}

void readMeasureBuffer(void){
  debug_msg_ln("measurebuffer: Read MeasureBuffer... ", DEBUG_VALUES);
  for (int i = 0; i < 24; ++i) {
    if (MeasureBuffer[i] != -1) {
      debug_msg(i, DEBUG_VALUES);
      debug_msg(": ", DEBUG_VALUES);
      debug_msg(MeasureBuffer[i], DEBUG_VALUES);
      debug_msg(" / ", DEBUG_VALUES);
    }
  }
  //debug_msg_ln("DONE", DEBUG_VALUES);
  debug_msg_ln("", DEBUG_VALUES);
  debug_msg_ln("measurebuffer: Read MeasureBuffer... DONE", DEBUG_VALUES);
}

void clearMeasureBuffer(void){
  debug_msg("measurebuffer: Clear MeasureBuffer... ", DEBUG_VALUES);
  for (int i = 0; i < 24; ++i) {
    MeasureBuffer[i] = -1;
  }
  debug_msg_ln("DONE", DEBUG_VALUES);
}