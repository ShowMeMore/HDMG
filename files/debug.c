#define DEBUG_STATE true
#define DEBUG_VALUES true
#define DEBUG_LED true
#define DEBUG_CHIRP true


void debug_setup(boolean state) {
    if (state) {
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