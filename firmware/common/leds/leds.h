/**
 * Leds module
 */

#ifndef _LEDS_H
#define _LEDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stdbool.h"

typedef enum {
    LED_OFF,
    LED_ON,
} leds_mode_t;

typedef enum {
    LED_GREEN,
    LED_RED,
    LED_BLUE,
    NUM_LED  // Number of leds, should be the last element
} leds_type_t;

typedef struct {
    bool modes[NUM_LED];
} leds_t;

void leds_init(leds_t* state);
void leds_on(leds_t* state, leds_type_t led_type);
void leds_off(leds_t* state, leds_type_t led_type);
void leds_toggle(leds_t* state, leds_type_t led_type);

#ifdef __cplusplus
}
#endif

#endif  // _LEDS_H