#ifndef VCOM_CONSOLE_H
#define VCOM_CONSOLE_H

#include "console.h"
#include "stdbool.h"

bool vcom_console_init(console_t* state);
void vcom_console_process(console_t* console_status);

#endif  // VCOM_CONSOLE_H
