#include "component.h"

bool component_init(component_t* state) {
    state->type = COMPONENT_NONE;
    return true;
}

// TODO: impl
void component_to_str(component_t* component) {
    switch (component->type) {
        case COMPONENT_NONE:
            break;
        case COMPONENT_RESISTOR:
            printf("Resistor: %ld Ohm\n", component->resistance);
            break;
        case COMPONENT_CAPACITOR:
            printf("Capacitor: %ld F\n", component->capacitance);
            break;
        case COMPONENT_DIODE:

            printf("Diode: Anode=%c, Cathode=%c\n", component->diode.anode, component->diode.cathode);
            break;
        case COMPONENT_TRANSISTOR:
            printf(
                "Transistor: Base=%c, Emitter=%c, Collector=%c\n", component->transistor.base,
                component->transistor.emitter, component->transistor.collector
            );
            break;
    }
}
