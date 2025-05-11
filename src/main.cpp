#include <Arduino.h>

const int RED_LED_PIN = 13;
const int YELLOW_LED_PIN = 12;
const int GREEN_LED_PIN = 11;
const int BUTTON_PIN = 2;
const int TRIG_PIN = 8;
const int ECHO_PIN = 7;

int lastButtonState = LOW;
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;

bool buttonPressed = false;

void checkLEDs();
void checkButton();
void checkSensor();

void setup() {
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(YELLOW_LED_PIN, OUTPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);
  
  pinMode(BUTTON_PIN, INPUT);
  
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  Serial.begin(9600);
}

void loop() {
  checkLEDs();
  // checkButton();
  // checkSensor();
}

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

  Serial.println(duration * 0.034 / 2);
}