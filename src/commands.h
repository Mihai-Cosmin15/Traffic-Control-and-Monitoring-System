#ifndef COMMANDS_H
#define COMMANDS_H

#include <Arduino.h>
#include "macros.h"
#include "usart.h"

void download_data(int &car_count);
void manage_command(char command[], int &car_count);

#endif