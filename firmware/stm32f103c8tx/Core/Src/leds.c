/**
 * Implementation leds module
 */

#include "leds.h"

#include "console.h"
#include "main.h"
#include "stm32f1xx_ll_gpio.h"

typedef struct {
    GPIO_TypeDef* port;
    uint32_t pin;
} leds_pad_t;

static leds_pad_t _pads_arr[NUM_LED] = {
    [LED_RED] = {LED_GPIO_Port, LED_Pin},
    [LED_TRANSISTOR] = {LED_Transistor_GPIO_Port, LED_Transistor_Pin},
    [LED_DIODE] = {LED_Diode_GPIO_Port, LED_Diode_Pin},
    [LED_CAPACITOR] = {LED_Capacitor_GPIO_Port, LED_Capacitor_Pin},
    [LED_RESISTOR] = {LED_Resistor_GPIO_Port, LED_Resistor_Pin},
};

void leds_init(leds_t* state) {
    for (int i = 0; i < NUM_LED; ++i) {
        state->modes[i] = false;
        leds_off(state, i);
    }
}

bool leds_on(leds_t* state, leds_type_t led_type) {
    if (led_type >= NUM_LED) {
        return false;
    }
    state->modes[led_type] = true;
    LL_GPIO_SetOutputPin(_pads_arr[led_type].port, _pads_arr[led_type].pin);
    return true;
}
bool leds_off(leds_t* state, leds_type_t led_type) {
    if (led_type >= NUM_LED) {
        return false;
    }
    state->modes[led_type] = false;
    LL_GPIO_ResetOutputPin(_pads_arr[led_type].port, _pads_arr[led_type].pin);
    return true;
}

bool leds_toggle(leds_t* state, leds_type_t led_type) {
    if (led_type >= NUM_LED) {
        return false;
    }
    state->modes[led_type] = state->modes[led_type] ? false : true;
    LL_GPIO_TogglePin(_pads_arr[led_type].port, _pads_arr[led_type].pin);
    return true;
}
