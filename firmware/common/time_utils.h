#ifndef DELAY_H
#define DELAY_H

#include <stdint.h>

void delay_ms(uint32_t ms);

uint32_t get_tick_count(void);

#endif  // DELAY_H
