#include <stdint.h>

#include "stm32f1xx_ll_utils.h";
#include "time_utils.h"

extern uint32_t tick_counter;

void delay_ms(uint32_t ms) { LL_mDelay(ms); }
uint32_t get_tick_count(void) { return tick_counter; }
