#include <Arduino.h>
#include "macros.h"
#include "utils.h"
#include "test.h"

#define TEST_NO 4

void setup() {
  initLEDs();
  initButton();
  initDistanceSensor();

  Serial.begin(9600);
}

void loop() {
  check(TEST_NO);
}
