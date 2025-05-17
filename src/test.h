#ifndef TEST_H
#define TEST_H

void checkLEDs();
void checkButton(unsigned long &last_debounce_time, unsigned long &debounce_delay, int &last_button_state, bool &button_pressed);
void checkSensor();
void checkBuzzer();
void check(int testNo, unsigned long &last_debounce_time, unsigned long &debounce_delay, int &last_button_state, bool &button_pressed);

#endif
