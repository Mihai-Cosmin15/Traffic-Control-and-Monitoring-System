#ifndef MACROS_H
#define MACROS_H

#define RED_DDR DDRB
#define RED_PORT PORTB
#define RED_BIT PORTB5

#define YELLOW_DDR DDRB
#define YELLOW_PORT PORTB
#define YELLOW_BIT PORTB4

#define GREEN_DDR DDRB
#define GREEN_PORT PORTB
#define GREEN_BIT PORTB3

#define GREEN_LIGHT 0
#define RED_LIGHT 1
#define YELLOW_LIGHT 2
#define BLINKING_GREEN_LIGHT 3

const int RED_LED_PIN = 13;
const int YELLOW_LED_PIN = 12;
const int GREEN_LED_PIN = 11;

const int BUTTON_PIN = 2;
const int TRIG_PIN = 8;
const int ECHO_PIN = 7;
const int BUZZER_PIN = 3;

#endif
