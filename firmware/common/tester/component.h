#ifndef COMPONENT_H
#define COMPONENT_H

#include "pin.h"
#include "stdint.h"

typedef enum component_type {
    COMPONENT_NONE = 0,
    COMPONENT_TRANSISTOR,
    COMPONENT_DIODE,
    COMPONENT_RESISTOR,
    COMPONENT_CAPACITOR,
} component_type_t;

typedef struct component {
    component_type_t type;

    union {
        uint32_t resistance;
        uint32_t capacitance;

        struct {
            char anode;
            char cathode;
        } diode;

        struct {
            char base;
            char emitter;
            char collector;
        } transistor;
    }
} component_t;

bool component_init(component_t* state);

#endif  // COMPONENT_H
