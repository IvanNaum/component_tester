
#include "tester_impl.h"

#include "main.h"

static pin_t _pinA, _pinB, _pinC;

static uint16_t _pin_get_raw_adc(struct pin* state);
static bool _pin_set_mode_func(struct pin* state, pin_type_t pin_type, pin_mode_t pin_mode);

static pad_t _pinsA[NUMS_PIN_TYPE] = {
    [PIN_TYPE_MIN_RESISTANT] = {PIN_A_0Ohm_GPIO_Port, PIN_A_0Ohm_Pin},
    [PIN_TYPE_MID_RESISTANT] = {PIN_A_680Ohms_GPIO_Port, PIN_A_680Ohms_Pin},
    [PIN_TYPE_MAX_RESISTANT] = {PIN_A_470kOhms_GPIO_Port, PIN_A_470kOhms_Pin},
    // [PIN_TYPE_ADC] = {},
};
static pad_t _pinsB[NUMS_PIN_TYPE] = {
    [PIN_TYPE_MIN_RESISTANT] = {PIN_B_0Ohm_GPIO_Port, PIN_B_0Ohm_Pin},
    [PIN_TYPE_MID_RESISTANT] = {PIN_B_680Ohms_GPIO_Port, PIN_B_680Ohms_Pin},
    [PIN_TYPE_MAX_RESISTANT] = {PIN_B_470kOhms_GPIO_Port, PIN_B_470kOhms_Pin},
    // [PIN_TYPE_ADC] = {},
};
static pad_t _pinsC[NUMS_PIN_TYPE] = {
    [PIN_TYPE_MIN_RESISTANT] = {PIN_C_0Ohm_GPIO_Port, PIN_C_0Ohm_Pin},
    [PIN_TYPE_MID_RESISTANT] = {PIN_C_680Ohms_GPIO_Port, PIN_C_680Ohms_Pin},
    [PIN_TYPE_MAX_RESISTANT] = {PIN_C_470kOhms_GPIO_Port, PIN_C_470kOhms_Pin},
    // [PIN_TYPE_ADC] = {},
};

void tester_impl_init(tester_t* state) {
    pin_init(&_pinA, 'A', &_pinsA, _pin_set_mode_func);
    pin_init(&_pinB, 'B', &_pinsB, _pin_set_mode_func);
    pin_init(&_pinC, 'C', &_pinsC, _pin_set_mode_func);

    tester_init(state, &_pinA, &_pinB, &_pinC);
}

static uint16_t _pin_get_raw_adc(struct pin* state) { return 0; }
static bool _pin_set_mode_func(struct pin* state, pin_type_t pin_type, pin_mode_t pin_mode) {
    switch (pin_mode) {
        case PIN_MODE_PUSH_PULL_LOW:
            /* code */
            break;
        case PIN_MODE_PUSH_PULL_HIGH:
            /* code */
            break;
        case PIN_MODE_OPEN_DRAIN_LOW:
            /* code */
            break;
        case PIN_MODE_OPEN_DRAIN_HIGH:
            /* code */
            break;
        default:
            return false;
    }
    return true;
}
