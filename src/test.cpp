#include <Arduino.h>
#include "test.h"
#include "macros.h"

int lastButtonState = LOW;
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;

bool buttonPressed = false;

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

void checkButton()
{
  int reading = digitalRead(BUTTON_PIN);

  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading == HIGH && !buttonPressed) {
      Serial.println("Button pressed");
      buttonPressed = true;
    } else if (reading == LOW && buttonPressed) {
      Serial.println("Button released");
      buttonPressed = false;
    }
  }

  lastButtonState = reading;
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

void check(int testNo)
{
  switch (testNo)
  {
  case 1:
    checkLEDs();
    break;
  case 2:
    checkButton();
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
