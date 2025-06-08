#include "pin.h"

#define _DEFAULT_MODE (PIN_MODE_OPEN_DRAIN_HIGH)

bool pin_init(pin_t* state, char name, struct pad* pins, pin_set_mode_func set_mode) {
    state->name = name;
    state->pins = pins;
    state->set_mode = set_mode;
    for (int i = 0; i < NUMS_PIN_TYPE; ++i) {
        state->set_mode(state, i, _DEFAULT_MODE);
        state->mode[i] = _DEFAULT_MODE;
    }
    return true;
}

pin_mode_t pin_get_mode(pin_t* state, pin_type_t pin_type) { return state->mode[pin_type]; }