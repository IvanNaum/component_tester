#include "tester.h"

bool tester_init(tester_t* state, pin_t pin_A, pin_t pin_B, pin_t pin_C) {
    state->pin_A = pin_A;
    state->pin_B = pin_B;
    state->pin_C = pin_C;
}
component_t tester_test(tester_t* state) {
    component_t component;
    component_init(&component);

    component = tester_test_transistor(state);
    if (COMPONENT_NONE != component.type) {
        return component;
    }
    component = tester_test_diode(state);
    if (COMPONENT_NONE != component.type) {
        return component;
    }
    component = tester_test_resistor(state);
    if (COMPONENT_NONE != component.type) {
        return component;
    }
    component = tester_test_capacitor(state);
    if (COMPONENT_NONE != component.type) {
        return component;
    }
    return component;
}

component_t tester_test_transistor(tester_t* state);
component_t tester_test_diode(tester_t* state);
component_t tester_test_resistor(tester_t* state) {
    // 680 Ohms
    // 1. Установка pin1 680 в GND
    // 1. Установка pin2 0 в VCC
    // 1. Установка pin1 АЦП
    // 1. Установка pin2 АЦП
    // pin_A - pin_B
    // pin_A - pin_C
    // pin_B - pin_C
    // 470k Ohms
}
component_t tester_test_capacitor(tester_t* state);