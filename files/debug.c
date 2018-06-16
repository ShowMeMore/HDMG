#if (DEBUG_MODE)
    #define DEBUG_STATE false
    #define DEBUG_VALUES true
    #define DEBUG_LED false
    #define DEBUG_CHIRP false
#endif

#if (!DEBUG_MODE)
    #define DEBUG_STATE false
    #define DEBUG_VALUES false
    #define DEBUG_LED false
    #define DEBUG_CHIRP false 
#endif

void debug_setup() {
    if (DEBUG_STATE || DEBUG_VALUES || DEBUG_LED || DEBUG_CHIRP) {
        Serial.begin(9600);
    }
}

void debug_stop() {
    if (DEBUG_STATE || DEBUG_VALUES || DEBUG_LED || DEBUG_CHIRP) {
        Serial.end();
    }
}

void debug_msg_ln(String msg, boolean cond) {
    if (cond) {
        Serial.println(msg);
    }
}

void debug_msg(String msg, boolean cond) {
    if (cond) {
        Serial.print(msg);
    }
}

void debug_msg_ln(float msg, boolean cond) {
    if (cond) {
        Serial.println(msg);
    }
}

void debug_msg(float msg, boolean cond) {
    if (cond) {
        Serial.print(msg);
    }
}

void debug_msg_ln(unsigned int msg, boolean cond) {
    if (cond) {
        Serial.println(msg);
    }
}

void debug_msg(unsigned int msg, boolean cond) {
    if (cond) {
        Serial.print(msg);
    }
}

void debug_msg_ln(int msg, boolean cond) {
    if (cond) {
        Serial.println(msg);
    }
}
    
void debug_msg(int msg, boolean cond) {
    if (cond) {
        Serial.print(msg);
    }
}