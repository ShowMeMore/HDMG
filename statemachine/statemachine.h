// define different states
const int MEASURE = 1;
const int CONNECT = 2;
const int SEND = 3;
const int SLEEP = 4;

void mTicker_handle(void);
void sTicker_handle(void);
void lTicker_handle(void);