#include "commands.h"

void download_data()
{
    char buffer[SMALL_BUFFER_SIZE];

    sprintf(buffer, "%d", total_car_count);
    USART0_print("Cars passed (since last download): ");
    USART0_println(buffer);

    dtostrf((double) traffic_vol, 4, 2, buffer);
    USART0_print("Traffic volume score: ");
    USART0_println(buffer);

    dtostrf((double) traffic_trend, 4, 2, buffer);
    USART0_print("Traffic trend score: ");
    USART0_println(buffer);

    dtostrf((double) traffic_score, 4, 2, buffer);
    USART0_print("Traffic score (overall): ");
    USART0_println(buffer);

    total_car_count = 0;
}

void debug()
{
    char buffer[SMALL_BUFFER_SIZE];

    sprintf(buffer, "%d", interval_car_count);
    USART0_print("Fast debug\nNumber of cars (in this interval): ");
    USART0_println(buffer);

    sprintf(buffer, "%d", last_interval_car_count);
    USART0_print("Number of cars (in last interval): ");
    USART0_println(buffer);

    sprintf(buffer, "%d", total_car_count);
    USART0_print("Number of cars (since last download): ");
    USART0_println(buffer);

    dtostrf((double) traffic_vol, 4, 2, buffer);
    USART0_print("Traffic volume score: ");
    USART0_println(buffer);

    dtostrf((double) traffic_trend, 4, 2, buffer);
    USART0_print("Traffic trend score: ");
    USART0_println(buffer);

    dtostrf((double) traffic_score, 4, 2, buffer);
    USART0_print("Traffic score (overall): ");
    USART0_println(buffer);

    sprintf(buffer, "%d", green_light_time);
    USART0_print("Current green light time: ");
    USART0_println(buffer);
}

void showcase()
{
    int rand_cars = random(50, 200);
    if (last_interval_car_count == -1)
        last_interval_car_count = rand_cars;
    interval_car_count = rand_cars;
    interval_timer = INTERVAL_TIME + 1;

    char buffer[SMALL_BUFFER_SIZE];
    sprintf(buffer, "%d", interval_car_count);
    USART0_print("Showcase\nNumber of cars chosen for this interval: ");
    USART0_println(buffer);

    apply_traffic_formula();
    debug();
    
    to_green_light();
}

void manage_command(char command[])
{
    if (strncmp(command, "download", strlen("download")) == 0) {
        download_data();
    } else if (strncmp(command, "debug", strlen("debug")) == 0) {
        debug();
    } else if (strncmp(command, "showcase", strlen("showcase")) == 0) {
        showcase();
    } else {
        USART0_print("Command error 2\n");
    }
}
