#include <stdint.h>

#include "commands.h"
#include "console.h"
#include "leds.h"

extern leds_t leds_status;

void leds_func(console_t* state, char* command_line, uint16_t arg_shifts[], uint8_t nargs) {
    if (nargs == 1) {
        state->write(state->commands[COMMAND_LED].description);
        state->write("\r\n");
    } else if (nargs == 2) {
        state->write("Arguments error\r\n");
    } else if (nargs == 3) {
        const char* led_type_str = &command_line[arg_shifts[1]];
        const char* led_mode_str = &command_line[arg_shifts[2]];

        leds_type_t led_type;
        if (strcmp(led_type_str, "tran") == 0) {
            led_type = LED_TRANSISTOR;
        } else if (strcmp(led_type_str, "diode") == 0) {
            led_type = LED_DIODE;
        } else if (strcmp(led_type_str, "resistor") == 0) {
            led_type = LED_RESISTOR;
        } else if (strcmp(led_type_str, "cap") == 0) {
            led_type = LED_CAPACITOR;
        } else {
            state->write("Unknown led\r\n");
            return;
        }

        if (strcmp(led_mode_str, "on") == 0) {
            leds_on(&leds_status, led_type);
        } else if (strcmp(led_mode_str, "off") == 0) {
            leds_off(&leds_status, led_type);
        } else if (strcmp(led_mode_str, "toggle") == 0) {
            leds_toggle(&leds_status, led_type);
        } else {
            state->write("Led mode error");
            return;
        }

        sprintf(console_tx_buffer, "led: %s\r\nmode: %s", led_type_str, led_mode_str);
        state->write(console_tx_buffer);
    } else {
        state->write("Too many arguments\r\n");
    }
}