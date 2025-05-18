#include "utils.h"

int last_beep;
int beep_time = 200;
bool beep = false;

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

int traffic_formula()
{
	return STANDARD_GREEN_TIME + interval_car_count;
}

void to_green_light()
{
	setLEDs(false, false, true);
	stopBuzzer();
	state = GREEN_LIGHT;
	timer = 0;

	if (interval_timer > INTERVAL_TIME) {
		update_green_light_time();
	}
}

void to_red_light()
{
	setLEDs(true, false, false);
	last_beep = millis();
	beep = false;
	// greenLightBeep();
	state = RED_LIGHT;
}

void to_yellow_light()
{
	setLEDs(false, true, false);
	stopBuzzer();
	state = YELLOW_LIGHT;
	timer = 0;
}

void to_blinking_green_light()
{
	setLEDs(false, false, false);
	state = BLINKING_GREEN_LIGHT;
	blinking_count = 0;
	timer = 0;
}

void update_green_light_time()
{
	green_light_time = traffic_formula();
	interval_timer = 0;
	interval_car_count = 0;
}
