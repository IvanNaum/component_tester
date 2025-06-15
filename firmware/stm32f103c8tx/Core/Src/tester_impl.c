
#include "tester_impl.h"

#include "main.h"
#include "stm32_common.h"

static pin_t _pinA, _pinB, _pinC;

static uint16_t _pin_get_raw_adc(struct pin* state);
static bool _pin_set_mode_func(struct pin* state, pin_type_t pin_type, pin_mode_t pin_mode);

static pad_t _pinsA[NUMS_PIN_TYPE] = {
    [PIN_TYPE_MIN_RESISTANT] = {PIN_A_0Ohm_GPIO_Port, PIN_A_0Ohm_Pin},
    [PIN_TYPE_MID_RESISTANT] = {PIN_A_680Ohms_GPIO_Port, PIN_A_680Ohms_Pin},
    [PIN_TYPE_MAX_RESISTANT] = {PIN_A_470kOhms_GPIO_Port, PIN_A_470kOhms_Pin},
    [PIN_TYPE_ADC] = {PIN_A_ADC_GPIO_Port, PIN_A_ADC_Pin},
};
static pad_t _pinsB[NUMS_PIN_TYPE] = {
    [PIN_TYPE_MIN_RESISTANT] = {PIN_B_0Ohm_GPIO_Port, PIN_B_0Ohm_Pin},
    [PIN_TYPE_MID_RESISTANT] = {PIN_B_680Ohms_GPIO_Port, PIN_B_680Ohms_Pin},
    [PIN_TYPE_MAX_RESISTANT] = {PIN_B_470kOhms_GPIO_Port, PIN_B_470kOhms_Pin},
    [PIN_TYPE_ADC] = {PIN_B_ADC_GPIO_Port, PIN_B_ADC_Pin},
};
static pad_t _pinsC[NUMS_PIN_TYPE] = {
    [PIN_TYPE_MIN_RESISTANT] = {PIN_C_0Ohm_GPIO_Port, PIN_C_0Ohm_Pin},
    [PIN_TYPE_MID_RESISTANT] = {PIN_C_680Ohms_GPIO_Port, PIN_C_680Ohms_Pin},
    [PIN_TYPE_MAX_RESISTANT] = {PIN_C_470kOhms_GPIO_Port, PIN_C_470kOhms_Pin},
    [PIN_TYPE_ADC] = {PIN_C_ADC_GPIO_Port, PIN_C_ADC_Pin},
};

void tester_impl_init(tester_t* state) {
    pin_init(&_pinA, 'A', &_pinsA, _pin_set_mode_func);
    pin_init(&_pinB, 'B', &_pinsB, _pin_set_mode_func);
    pin_init(&_pinC, 'C', &_pinsC, _pin_set_mode_func);

    tester_init(state, &_pinA, &_pinB, &_pinC);
}

static bool _pin_set_mode_func(struct pin* state, pin_type_t pin_type, pin_mode_t pin_mode) {
    GPIO_TypeDef* port = state->pins[pin_type].port;
    uint32_t pin = state->pins[pin_type].pin;

    switch (pin_mode) {
        case PIN_MODE_PUSH_PULL_LOW:
            LL_GPIO_SetPinOutputType(port, pin, LL_GPIO_OUTPUT_PUSHPULL);
            LL_GPIO_ResetOutputPin(port, pin);
            break;

        case PIN_MODE_PUSH_PULL_HIGH:
            LL_GPIO_SetPinOutputType(port, pin, LL_GPIO_OUTPUT_PUSHPULL);
            LL_GPIO_SetOutputPin(port, pin);
            break;

        case PIN_MODE_OPEN_DRAIN_LOW:
            LL_GPIO_SetPinOutputType(port, pin, LL_GPIO_OUTPUT_OPENDRAIN);
            LL_GPIO_ResetOutputPin(port, pin);
            break;

        case PIN_MODE_OPEN_DRAIN_HIGH:
            LL_GPIO_SetPinOutputType(port, pin, LL_GPIO_OUTPUT_OPENDRAIN);
            LL_GPIO_SetOutputPin(port, pin);
            break;

        default:
            return false;
    }
    return true;
}

static uint16_t _pin_get_raw_adc(struct pin* state) {
    uint16_t adc_value = 0;

    // 1.  Убедитесь, что ADC включен. Если нет, включите его.
    if (!LL_ADC_IsEnabled(ADC1)) {
        LL_ADC_Enable(ADC1);
        LL_mDelay(1);
        while (!LL_ADC_IsActiveFlag_ADRDY(ADC1)) {
        }
    }
    LL_ADC_REG_StartConversionSWStart(ADC1);
    while (!LL_ADC_IsActiveFlag_EOCS(ADC1)) {
    }

    switch (state->pins[PIN_TYPE_ADC].pin) {
        case LL_GPIO_PIN_0:
            adc_value = LL_ADC_REG_ReadConversion(ADC1);
            break;
        case LL_GPIO_PIN_1:
            LL_ADC_REG_StartConversionSWStart(ADC1);
            while (!LL_ADC_IsActiveFlag_EOCS(ADC1)) {
            }
            adc_value = LL_ADC_REG_ReadConversion(ADC1);
            break;
        case LL_GPIO_PIN_2:
            LL_ADC_REG_StartConversionSWStart(ADC1);
            while (!LL_ADC_IsActiveFlag_EOCS(ADC1)) {
            }
            LL_ADC_REG_StartConversionSWStart(ADC1);
            while (!LL_ADC_IsActiveFlag_EOCS(ADC1)) {
            }
            adc_value = LL_ADC_REG_ReadConversion(ADC1);
            break;
        default:
            return 0;
    }

    LL_ADC_ClearFlag_EOCS(ADC1);

    return adc_value;
}