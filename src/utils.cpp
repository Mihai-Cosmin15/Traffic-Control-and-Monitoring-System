#include "utils.h"

void initLEDs()
{
	RED_DDR |= (1 << RED_BIT);
	YELLOW_DDR |= (1 << YELLOW_BIT);
	GREEN_DDR |= (1 << GREEN_BIT);
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

void setLEDs(bool red, bool yellow, bool green)
{
	red ? RED_PORT |= (1 << RED_BIT) : RED_PORT &= ~(1 << RED_BIT);
	yellow ? YELLOW_PORT |= (1 << YELLOW_BIT) : YELLOW_PORT &= ~(1 << YELLOW_BIT);
	green ? GREEN_PORT |= (1 << GREEN_BIT) : GREEN_PORT &= ~(1 << GREEN_BIT);
}
