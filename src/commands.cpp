#include "commands.h"

void download_data(int &car_count)
{
    char buffer[SMALL_BUFFER_SIZE];
    sprintf(buffer, "%d", car_count);
    USART0_print("Cars passed: ");
    USART0_println(buffer);
    car_count = 0;
}

void manage_command(char command[], int &car_count)
{
    if (strncmp(command, "download", strlen("download")) == 0) {
        download_data(car_count);
    } else {
        USART0_print("Command error 2\n");
    }
}
