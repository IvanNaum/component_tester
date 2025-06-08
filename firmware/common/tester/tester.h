#ifndef TESTER_H
#define TESTER_H

#include "component.h"
#include "pin.h"

typedef struct tester {
    pin_t pin_A;
    pin_t pin_B;
    pin_t pin_C;
} tester_t;

bool tester_init(tester_t* state, pin_t pin_A, pin_t pin_B, pin_t pin_C);
component_t tester_test_transistor(tester_t* state);
component_t tester_test_diode(tester_t* state);
component_t tester_test_resistor(tester_t* state);
component_t tester_test_capacitor(tester_t* state);

#endif  // TESTER_H
