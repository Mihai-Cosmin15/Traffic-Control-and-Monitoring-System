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

#define BUTTON_DDR DDRD
#define BUTTON_PORT PORTD
#define BUTTON_PIN PIND
#define BUTTON_PIN_REG PD2
#define BUTTON_BIT 2

#define BUZZER_DDR DDRD
#define BUZZER_PORT PORTD
#define BUZZER_BIT 3

#define GREEN_LIGHT 0
#define RED_LIGHT 1
#define YELLOW_LIGHT 2
#define BLINKING_GREEN_LIGHT 3

#define CLOCK_SPEED 16000000
#define BAUD 9600
#define MYUBRR (CLOCK_SPEED/16/BAUD-1)

#define MAX_COMMAND_SIZE 32
#define SMALL_BUFFER_SIZE 10

const int RED_LED_PIN = 13;
const int YELLOW_LED_PIN = 12;
const int GREEN_LED_PIN = 11;

const int _BUTTON_PIN = 2;
const int TRIG_PIN = 8;
const int ECHO_PIN = 7;
const int BUZZER_PIN = 3;

#endif
