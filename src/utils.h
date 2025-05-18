#ifndef UTILS_H
#define UTILS_H

#include <Arduino.h>
#include "macros.h"

void initLEDs();
void initButton();
void initDistanceSensor();
void initBuzzer();
void startBuzzer();
void stopBuzzer();
void setLEDs(bool red, bool yellow, bool green);
void greenLightBeep();
int traffic_formula();
void to_green_light();
void to_red_light();
void to_yellow_light();
void to_blinking_green_light();
void update_green_light_time();

#endif
