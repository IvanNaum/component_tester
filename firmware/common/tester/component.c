#include "component.h"

bool component_init(component_t* state) {
    state->type = COMPONENT_NONE;
    return true;
}

void component_to_str(component_t* component, char* buffer) {
    switch (component->type) {
        case COMPONENT_NONE:
            sprintf(buffer, "Component is not detected\r\n");
            break;
        case COMPONENT_RESISTOR:
            sprintf(buffer, "Resistor: %ld Ohm\r\n", component->resistance);
            break;
        case COMPONENT_CAPACITOR:
            sprintf(buffer, "Capacitor: %ld F\r\n", component->capacitance);
            break;
        case COMPONENT_DIODE:

            sprintf(buffer, "Diode: Anode=%c, Cathode=%c\r\n", component->diode.anode, component->diode.cathode);
            break;
        case COMPONENT_TRANSISTOR:
            sprintf(
                buffer, "Transistor: Base=%c, Emitter=%c, Collector=%c\r\n", component->transistor.base,
                component->transistor.emitter, component->transistor.collector
            );
            break;
    }
}
