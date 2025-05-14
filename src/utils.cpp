#include "utils.h"

void initLEDs()
{
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(YELLOW_LED_PIN, OUTPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);
}

void initButton()
{
  pinMode(BUTTON_PIN, INPUT);
}

void initDistanceSensor()
{
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
}

void initBuzzer()
{
  pinMode(BUZZER_PIN, OUTPUT);
}
