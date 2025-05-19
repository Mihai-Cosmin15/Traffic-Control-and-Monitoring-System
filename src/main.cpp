#include <Arduino.h>
#include "macros.h"
#include "utils.h"
#include "test.h"
#include "timers.h"
#include "usart.h"
#include "commands.h"

#define TEST_NO 1

int green_light_time = STANDARD_GREEN_TIME;
int total_car_count = 0, interval_car_count = 0;
bool car_detected = false;
int command_size = 0;
char command[MAX_COMMAND_SIZE];

uint8_t state = 0;
int blinking_count = 0, time_passed = 0, start_time = 0, timer = 0, interval_timer = 0;
bool button_change = false;

int last_button_state = LOW;
unsigned long last_debounce_time = 0;
unsigned long debounce_delay = 50;

bool button_pressed = false;

unsigned long last_detection = 0;

ISR(TIMER1_COMPA_vect)
{
	interval_timer++;
	timer++;
}

ISR(PCINT2_vect)
{
	button_change = true;
}

void setup() {

	initLEDs();
	initButton();
	initBuzzer();
	initDistanceSensor();

	init_timer1();
	init_timer2();

	setLEDs(false, false, true);

	// Serial.begin(9600);
	USART0_init(MYUBRR);
	
	sei();
}

void loop() {
	// check(TEST_NO, last_debounce_time, debounce_delay, last_button_state, button_pressed);
	char received;
	if (USART0_receive_nonblocking(received)) {
		USART0_print(&received);
		if (received == '\n' || received == '\r') {
			command[command_size++] = '\0';
			manage_command(command);
			strcpy(command, "");
			command_size = 0;
		} else if (isAlphaNumeric(received)){
			if (command_size < MAX_COMMAND_SIZE) {
				command[command_size++] = received;
			} else {
				USART0_print("Command error 1\n");
				strcpy(command, "");
				command_size = 0;
			}
		}
	}

	switch(state) {
	case GREEN_LIGHT:
		if (timer > green_light_time) {
			to_blinking_green_light();
		}

		break;
	case RED_LIGHT:
		greenLightBeep();
		if (timer > 5) {
			to_green_light();
		}

		break;
	case YELLOW_LIGHT:
		if (timer > 2) {
			to_red_light();
		}

		break;
	case BLINKING_GREEN_LIGHT:
		if (timer > 0) {
			GREEN_PORT ^= (1 << GREEN_BIT);
			timer = 0;
			blinking_count++;

			if (blinking_count == 5) {
				to_yellow_light();
			}
		}
		break;
	default:
		break;
	}

	if (button_change == true) {
		int current_time = millis();

		if (current_time - last_debounce_time > debounce_delay) {
			int reading = (BUTTON_PIN & (1 << BUTTON_BIT)) ? HIGH : LOW;
			if (reading == HIGH && last_button_state == LOW) {
				if (state == GREEN_LIGHT) {
					timer = max(timer, green_light_time * 3 / 4);
					char buffer[20];
					itoa(timer, buffer, 10);
					USART0_println(buffer);
				}
				button_pressed = true;
			} else if (reading == LOW && last_button_state == HIGH) {
				button_pressed = false;
			}
			last_debounce_time = current_time;
			last_button_state = reading;
		}
		button_change = false;
	}
	
	digitalWrite(TRIG_PIN, LOW);
	delayMicroseconds(2);
	digitalWrite(TRIG_PIN, HIGH);
	delayMicroseconds(10);
	digitalWrite(TRIG_PIN, LOW);
  
	int duration = pulseIn(ECHO_PIN, HIGH);
	int distance = duration / 29 / 2;
  
	// Serial.println(distance);

	unsigned long current_time = millis();
	if (distance < DISTANCE_TO_CAR && !car_detected && current_time - last_detection > debounce_delay) {
		total_car_count++;
		interval_car_count++;
		car_detected = true;
		last_detection = current_time;
	} else if (distance > DISTANCE_TO_CAR + 10 && car_detected && current_time - last_detection > debounce_delay) {
		car_detected = false;
		last_detection = current_time;
	}

	
}
