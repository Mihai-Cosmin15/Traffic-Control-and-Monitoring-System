#include "utils.h"

void initLEDs()
{
	RED_DDR |= (1 << RED_BIT);
	YELLOW_DDR |= (1 << YELLOW_BIT);
	GREEN_DDR |= (1 << GREEN_BIT);
}

void initButton()
{
	BUTTON_DDR &= ~(1 << BUTTON_BIT);
	BUTTON_PORT |= (1 << BUTTON_BIT);

	PCICR |= (1 << PCIE2);
	PCMSK2 |= (1 << PCINT18);
}

void initDistanceSensor()
{
	pinMode(TRIG_PIN, OUTPUT);
	pinMode(ECHO_PIN, INPUT);
}

void initBuzzer()
{
	BUZZER_DDR |= (1 << BUZZER_BIT);
}

void startBuzzer()
{
	TCCR2A |= (1 << COM2B1);
}

void stopBuzzer()
{
	TCCR2A &= ~(1 << COM2B1);
	BUZZER_PORT &= ~(1 << BUZZER_BIT);
}

void setLEDs(bool red, bool yellow, bool green)
{
	red ? RED_PORT |= (1 << RED_BIT) : RED_PORT &= ~(1 << RED_BIT);
	yellow ? YELLOW_PORT |= (1 << YELLOW_BIT) : YELLOW_PORT &= ~(1 << YELLOW_BIT);
	green ? GREEN_PORT |= (1 << GREEN_BIT) : GREEN_PORT &= ~(1 << GREEN_BIT);
}

void greenLightBeep()
{
	int last_beep = 0, beep_time = 100;
	bool beep = false;

	int current_time = millis();
	if (current_time - last_beep > beep_time) {
		if (beep) {
			stopBuzzer();
		} else {
			startBuzzer();
		}

		last_beep = current_time;
		beep = !beep;
	}
}
