/**
 * Leds module
 */

#ifndef LEDS_H
#define LEDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stdbool.h"

typedef enum {
    LED_OFF,
    LED_ON,
} leds_mode_t;

typedef enum {
    LED_RED,
    LED_RESISTOR,
    LED_CAPACITOR,
    LED_DIODE,
    LED_TRANSISTOR,
    NUM_LED  // Number of leds, should be the last element
} leds_type_t;

typedef struct {
    bool modes[NUM_LED];
} leds_t;

void leds_init(leds_t* state);
bool leds_on(leds_t* state, leds_type_t led_type);
bool leds_off(leds_t* state, leds_type_t led_type);
bool leds_toggle(leds_t* state, leds_type_t led_type);

#ifdef __cplusplus
}
#endif

#endif  // LEDS_H
