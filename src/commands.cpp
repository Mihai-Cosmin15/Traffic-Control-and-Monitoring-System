#include "commands.h"

void download_data()
{
    char buffer[SMALL_BUFFER_SIZE];
    sprintf(buffer, "%d", total_car_count);
    USART0_print("Cars passed: ");
    USART0_println(buffer);
    total_car_count = 0;
}

void debug()
{
    char buffer[SMALL_BUFFER_SIZE];

    sprintf(buffer, "%d", interval_car_count);
    USART0_print("Fast debug\nNumber of cars (in this interval): ");
    USART0_println(buffer);

    sprintf(buffer, "%d", total_car_count);
    USART0_print("Number of cars (since last download): ");
    USART0_println(buffer);

    sprintf(buffer, "%d", green_light_time);
    USART0_print("Current green light time: ");
    USART0_println(buffer);
}

void showcase()
{
    interval_car_count = 10;
    interval_timer = INTERVAL_TIME + 1;

    char buffer[SMALL_BUFFER_SIZE];
    sprintf(buffer, "%d", interval_car_count);
    USART0_print("Showcase\nNumber of cars: ");
    USART0_println(buffer);
    
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
