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

#endif
