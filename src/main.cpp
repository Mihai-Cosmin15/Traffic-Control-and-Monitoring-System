#include <Arduino.h>
#include "macros.h"
#include "utils.h"
#include "test.h"
#include "timers.h"

#define TEST_NO 1

uint8_t state = 0;
int blinking_count = 0, time_passed = 0, start_time = 0, timer = 0;

ISR(TIMER1_COMPA_vect)
{
	timer++;
}

void setup() {
	sei();

	initLEDs();
	// initButton();
	// initDistanceSensor();

	init_timer1();

	setLEDs(false, false, true);

	Serial.begin(9600);
}

void loop() {
  // check(TEST_NO);

	switch(state) {
	case GREEN_LIGHT:
		if (timer > 10) {
			setLEDs(false, false, false);
			state = BLINKING_GREEN_LIGHT;
			timer = 0;
		}

		break;
	case RED_LIGHT:
		if (timer > 5) {
			setLEDs(false, true, false);
			state = YELLOW_LIGHT;
			timer = 0;
		}

		break;
	case YELLOW_LIGHT:
		if (timer > 2) {
			setLEDs(false, false, true);
			state = GREEN_LIGHT;
			timer = 0;
		}

		break;
	case BLINKING_GREEN_LIGHT:
		if (timer > 0) {
			GREEN_PORT ^= (1 << GREEN_BIT);
			timer = 0;
			blinking_count++;

			if (blinking_count == 5) {
				setLEDs(true, false, false);
				state = RED_LIGHT;
				blinking_count = 0;
			}
		}
		break;
	default:
		break;
	}
}
