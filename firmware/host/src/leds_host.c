#include <stdio.h>

#include "console.h"
#include "leds.h"
#include "string.h"

extern leds_t leds;

void leds_func(console_t* state, char* command_line, uint16_t arg_shifts[], uint8_t nargs) {
    if (nargs == 1) {
        state->write("Arguments error\r\n");
        return;
    } else if (nargs > 3) {
        state->write("Arguments error\r\n");
        return;
    }

    char* type_str = &command_line[arg_shifts[1]];
    leds_type_t led_type;

    if (strcmp(type_str, "green") == 0) {
        led_type = LED_GREEN;
    } else if (strcmp(type_str, "blue") == 0) {
        led_type = LED_BLUE;
    } else if (strcmp(type_str, "red") == 0) {
        led_type = LED_RED;
    } else {
        state->write("Arguments error, unknown color\r\n");
        return;
    }

    if (nargs == 3) {
        char* mode_str = &command_line[arg_shifts[2]];

        if (strcmp(mode_str, "on") == 0) {
            leds_on(&leds, led_type);
        } else if (strcmp(mode_str, "off") == 0) {
            leds_off(&leds, led_type);
        } else {
            state->write("Arguments error, unknown mode\r\n");
            return;
        }
    }
    sprintf(console_tx_buffer, "led %s - %d\n\r", type_str, leds.modes[led_type]);
    state->write(console_tx_buffer);
}

void leds_init(leds_t* state) {
    for (int i = 0; i < NUM_LED; ++i) { state->modes[i] = LED_OFF; }
}
void leds_on(leds_t* state, leds_type_t led_type) { state->modes[led_type] = true; }
void leds_off(leds_t* state, leds_type_t led_type) { state->modes[led_type] = false; }
void leds_toggle(leds_t* state, leds_type_t led_type) { state->modes[led_type] = !state->modes[led_type]; }
