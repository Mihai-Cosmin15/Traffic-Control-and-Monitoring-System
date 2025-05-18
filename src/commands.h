#ifndef COMMANDS_H
#define COMMANDS_H

#include <Arduino.h>
#include "macros.h"
#include "usart.h"
#include "utils.h"

void download_data();
void manage_command(char command[]);

#endif