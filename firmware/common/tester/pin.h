#ifndef PIN_H
#define PIN_H

#include <stdbool.h>
#include <stdint.h>

typedef enum pin_mode {
    PIN_MODE_PUSH_PULL_LOW,
    PIN_MODE_PUSH_PULL_HIGH,
    PIN_MODE_OPEN_DRAIN_LOW,
    PIN_MODE_OPEN_DRAIN_HIGH,
    NUMS_PIN_MODE  // Number of modes, should be the last element
} pin_mode_t;

typedef enum pin_type {
    PIN_TYPE_MIN_RESISTANT,
    PIN_TYPE_MID_RESISTANT,
    PIN_TYPE_MAX_RESISTANT,
    PIN_TYPE_ADC,
    NUMS_PIN_TYPE  // Number of modes, should be the last element
} pin_type_t;

typedef uint16_t (*pin_get_raw_adc)(struct pin* state);
typedef bool (*pin_set_mode_func)(struct pin* state, pin_type_t pin_type, pin_mode_t pin_mode);

typedef struct pin {
    char name;
    struct pad* pins;
    pin_mode_t mode[NUMS_PIN_TYPE];
    pin_get_raw_adc get_raw_adc;
    pin_set_mode_func set_mode;
} pin_t;

bool pin_init(pin_t* state, char name, struct pad* pins, pin_set_mode_func set_mode);
pin_mode_t pin_set_mode(pin_t* state, pin_type_t pin_type, pin_mode_t pin_mode);
pin_mode_t pin_get_mode(pin_t* state, pin_type_t);

#endif  // PIN_H
