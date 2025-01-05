/**
 * Implementation leds module
 */

#include "leds.h"

#include "main.h"
#include "stm32f1xx_ll_gpio.h"

void leds_init(leds_t* state) {
    for (int i = 0; i < NUM_LED; ++i) {
        state->modes[i] = false;
        leds_off(state, i);
    }
}

void leds_on(leds_t* state, leds_type_t led_type) {
    if (led_type != LED_GREEN) { return; }
    state->modes[led_type] = true;
    LL_GPIO_ResetOutputPin(LED_GPIO_Port, LED_Pin);
}
void leds_off(leds_t* state, leds_type_t led_type) {
    if (led_type != LED_GREEN) { return; }
    state->modes[led_type] = false;
    LL_GPIO_SetOutputPin(LED_GPIO_Port, LED_Pin);
}

void leds_toggle(leds_t* state, leds_type_t led_type) {
    if (led_type != LED_GREEN) { return; }
    state->modes[led_type] = state->modes[led_type] ? false : true;
    LL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
}
