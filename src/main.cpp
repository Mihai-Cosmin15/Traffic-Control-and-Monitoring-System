#include <Arduino.h>
#include "macros.h"
#include "utils.h"
#include "test.h"

#define TEST_NO 1

uint8_t state = 0;
int blinking_count;

void setup() {
	initLEDs();
	initButton();
	initDistanceSensor();

	Serial.begin(9600);
}

void loop() {
  // check(TEST_NO);

	switch(state) {
	case GREEN_LIGHT:
		RED_PORT &= ~(1 << RED_BIT);
		YELLOW_PORT &= ~(1 << YELLOW_BIT);
		GREEN_PORT |= (1 << GREEN_BIT);
		delay(10000);

		blinking_count = 0;
		while (blinking_count < 4) {
			GREEN_PORT ^= (1 << GREEN_BIT);
			delay(500);
			blinking_count++;
		}

		state = RED_LIGHT;
		break;
	case RED_LIGHT:
		RED_PORT |= (1 << RED_BIT);
		YELLOW_PORT &= ~(1 << YELLOW_BIT);
		GREEN_PORT &= ~(1 << GREEN_BIT);

		delay(5000);

		state = YELLOW_LIGHT;

		break;
	case YELLOW_LIGHT:

		RED_PORT &= ~(1 << RED_BIT);
		YELLOW_PORT |= (1 << YELLOW_BIT);
		GREEN_PORT &= ~(1 << GREEN_BIT);

		delay(2000);

		state = GREEN_LIGHT;

		break;
	default:
		break;
	}
}
