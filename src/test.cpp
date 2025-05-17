#include <Arduino.h>
#include "test.h"
#include "macros.h"

void checkLEDs()
{
  digitalWrite(RED_LED_PIN, HIGH);
  delay(200);
  digitalWrite(RED_LED_PIN, LOW);
  delay(200);
  
  digitalWrite(YELLOW_LED_PIN, HIGH);
  delay(200);
  digitalWrite(YELLOW_LED_PIN, LOW);
  delay(200);

  digitalWrite(GREEN_LED_PIN, HIGH);
  delay(200);
  digitalWrite(GREEN_LED_PIN, LOW);
  delay(200);
}

void checkButton(unsigned long &last_debounce_time, unsigned long &debounce_delay, int &last_button_state, bool &button_pressed)
{
  int reading = digitalRead(_BUTTON_PIN);

  if (reading != last_button_state) {
    last_debounce_time = millis();
  }

  if ((millis() - last_debounce_time) > debounce_delay) {
    if (reading == HIGH && !button_pressed) {
      Serial.println("Button pressed");
      button_pressed = true;
    } else if (reading == LOW && button_pressed) {
      Serial.println("Button released");
      button_pressed = false;
    }
  }

  last_button_state = reading;
}

void checkSensor()
{
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  int duration = pulseIn(ECHO_PIN, HIGH);

  Serial.println(duration / 29 / 2);
}

void checkBuzzer()
{
  tone(BUZZER_PIN, 200);
  delay(500);
  noTone(BUZZER_PIN);
  delay(500);
}

void check(int testNo, unsigned long &last_debounce_time, unsigned long &debounce_delay, int &last_button_state, bool &button_pressed)
{
  switch (testNo)
  {
  case 1:
    checkLEDs();
    break;
  case 2:
    checkButton(last_debounce_time, debounce_delay, last_button_state, button_pressed);
    break;
  case 3:
    checkSensor();
    break;
  case 4:
    checkBuzzer();
    break;
  
  default:
    break;
  }
}
