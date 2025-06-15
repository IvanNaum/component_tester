#ifndef STM32_COMMON_H
#define STM32_COMMON_H

#include <stdint.h>

#include "stm32f1xx_ll_gpio.h"

typedef struct pad {
    GPIO_TypeDef* port;
    uint32_t pin;
} pad_t;

#endif  // STM32_COMMON_H
