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

void apply_traffic_formula()
{
	traffic_vol = min(1.0, (float)interval_car_count / MAX_CARS_PER_INTERVAL);
	traffic_trend = (float)(interval_car_count - last_interval_car_count) / MAX_CARS_PER_INTERVAL;
	
	float tmp_traffic_score = traffic_vol * TRAFFIC_WEIGHT + traffic_trend * TREND_WEIGHT;
	traffic_score = (float)1 / (1 + exp(-6 * (tmp_traffic_score - 0.5)));

	green_light_time = STANDARD_GREEN_TIME + traffic_score * (MAX_GREEN_TIME - STANDARD_GREEN_TIME);
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
	timer = 0;
	state = RED_LIGHT;
}

void to_yellow_light()
{
	setLEDs(false, true, false);
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
	if (last_interval_car_count == -1)
		last_interval_car_count = interval_car_count;
	apply_traffic_formula();
	interval_timer = 0;
	last_interval_car_count = interval_car_count;
	interval_car_count = 0;
}
