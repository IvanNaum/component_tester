#include "tester.h"

#include <math.h>

#include "time_utils.h"

#define _SUBTYPE_UNKNOWN ("xxx")
#define SUBTYPE_NPN ("NPN")
#define SUBTYPE_PNP ("PNP")

static float _measure_resistance(tester_t* state, pin_t* drive_pin, pin_t* measure_pin);
static float _calculate_resistance(uint16_t adc_value, float reference_resistor);
static void _reset_pins(tester_t* state);
static void _prepare_pins(tester_t* state);

bool tester_init(tester_t* state, pin_t* pin_A, pin_t* pin_B, pin_t* pin_C) {
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

component_t tester_test_transistor(tester_t* state) {
    _prepare_pins(state);

    component_t result;
    result.type = COMPONENT_TRANSISTOR;
    result.transistor.base = '?';       // Base
    result.transistor.collector = '?';  // Collector
    result.transistor.emitter = '?';    // Emitter
    result.transistor.subtype = _SUBTYPE_UNKNOWN;

    bool found = false;
    pin_t* pins[3] = {&state->pin_A, &state->pin_B, &state->pin_C};

    for (int i = 0; i < 3 && !found; i++) {
        for (int j = 0; j < 3 && !found; j++) {
            if (j == i)
                continue;
            for (int k = 0; k < 3 && !found; k++) {
                if (k == i || k == j)
                    continue;

                // Test NPN configuration
                pin_set_mode(pins[i], PIN_TYPE_MID_RESISTANT, PIN_MODE_PUSH_PULL_HIGH);
                pin_set_mode(pins[j], PIN_TYPE_MID_RESISTANT, PIN_MODE_OPEN_DRAIN_LOW);
                uint16_t be_adc = pins[j]->get_raw_adc(pins[j]);

                pin_set_mode(pins[i], PIN_TYPE_MID_RESISTANT, PIN_MODE_PUSH_PULL_HIGH);
                pin_set_mode(pins[k], PIN_TYPE_MID_RESISTANT, PIN_MODE_OPEN_DRAIN_LOW);
                uint16_t bc_adc = pins[k]->get_raw_adc(pins[k]);

                if (be_adc > 100 && be_adc < 4000 && bc_adc > 100 && bc_adc < 4000) {
                    result.transistor.base = 'A' + i;
                    result.transistor.collector = 'A' + k;
                    result.transistor.emitter = 'A' + j;
                    result.transistor.subtype = SUBTYPE_NPN;
                    found = true;
                    break;
                }

                // Test PNP configuration
                pin_set_mode(pins[i], PIN_TYPE_MID_RESISTANT, PIN_MODE_OPEN_DRAIN_LOW);
                pin_set_mode(pins[j], PIN_TYPE_MID_RESISTANT, PIN_MODE_PUSH_PULL_HIGH);
                be_adc = pins[j]->get_raw_adc(pins[j]);

                pin_set_mode(pins[i], PIN_TYPE_MID_RESISTANT, PIN_MODE_OPEN_DRAIN_LOW);
                pin_set_mode(pins[k], PIN_TYPE_MID_RESISTANT, PIN_MODE_PUSH_PULL_HIGH);
                bc_adc = pins[k]->get_raw_adc(pins[k]);

                if (be_adc > 100 && be_adc < 4000 && bc_adc > 100 && bc_adc < 4000) {
                    result.transistor.base = 'A' + i;
                    result.transistor.collector = 'A' + k;
                    result.transistor.emitter = 'A' + j;
                    result.transistor.subtype = SUBTYPE_PNP;
                    found = true;
                    break;
                }
            }
        }
    }

    // Reset all pins to safe state
    _reset_pins(state);

    return result;
}

component_t tester_test_diode(tester_t* state) {
    _prepare_pins(state);

    component_t result;
    result.type = COMPONENT_DIODE;
    result.diode.anode = '?';
    result.diode.cathode = '?';

    const pin_t* pins[3] = {&state->pin_A, &state->pin_B, &state->pin_C};
    bool found = false;

    for (int i = 0; i < 3 && !found; i++) {
        for (int j = 0; j < 3 && !found; j++) {
            if (i == j)
                continue;

            // Forward bias test
            pin_set_mode(pins[i], PIN_TYPE_MID_RESISTANT, PIN_MODE_PUSH_PULL_HIGH);
            pin_set_mode(pins[j], PIN_TYPE_MID_RESISTANT, PIN_MODE_OPEN_DRAIN_LOW);
            uint16_t forward_adc = pins[j]->get_raw_adc(pins[j]);

            // Reverse bias test
            pin_set_mode(pins[i], PIN_TYPE_MID_RESISTANT, PIN_MODE_OPEN_DRAIN_LOW);
            pin_set_mode(pins[j], PIN_TYPE_MID_RESISTANT, PIN_MODE_PUSH_PULL_HIGH);
            uint16_t reverse_adc = pins[j]->get_raw_adc(pins[j]);

            if (forward_adc > 1000 && forward_adc < 3000 && reverse_adc < 100) {
                result.diode.anode = 'A' + i;
                result.diode.cathode = 'A' + j;
                found = true;
            }
        }
    }

    // Reset all pins to safe state
    _reset_pins(state);

    return result;
}

component_t tester_test_resistor(tester_t* state) {
    _prepare_pins(state);

    component_t result;
    result.type = COMPONENT_RESISTOR;
    result.resistance = 0.0f;

    // Test all possible pin combinations (AB, AC, BC)
    float resistances[3] = {0};

    // Measure resistance between A-B
    resistances[0] = _measure_resistance(state, &state->pin_A, &state->pin_B);

    // Measure resistance between A-C
    resistances[1] = _measure_resistance(state, &state->pin_A, &state->pin_C);

    // Measure resistance between B-C
    resistances[2] = _measure_resistance(state, &state->pin_B, &state->pin_C);

    // Find the valid resistance (not zero and not infinite)
    for (int i = 0; i < 3; i++) {
        if (resistances[i] > 1.0f && resistances[i] < INFINITY) {
            result.resistance = resistances[i];
            break;
        }
    }

    // Reset all pins to safe state
    _reset_pins(state);

    return result;
}

component_t tester_test_capacitor(tester_t* state) {
    _prepare_pins(state);

    component_t result;
    result.type = COMPONENT_CAPACITOR;
    result.capacitance = 0.0f;

    pin_t* pins[3] = {&state->pin_A, &state->pin_B, &state->pin_C};
    bool measured = false;

    for (int i = 0; i < 3 && !measured; i++) {
        for (int j = i + 1; j < 3 && !measured; j++) {
            // Discharge capacitor first
            pin_set_mode(pins[i], PIN_TYPE_MIN_RESISTANT, PIN_MODE_PUSH_PULL_LOW);
            pin_set_mode(pins[j], PIN_TYPE_MIN_RESISTANT, PIN_MODE_PUSH_PULL_LOW);
            delay_ms(100);

            // Charge through known resistor (680Ω)
            pin_set_mode(pins[i], PIN_TYPE_MID_RESISTANT, PIN_MODE_PUSH_PULL_HIGH);
            pin_set_mode(pins[j], PIN_TYPE_MID_RESISTANT, PIN_MODE_OPEN_DRAIN_LOW);

            // Measure charge time
            uint32_t start_time = get_tick_count();
            uint16_t adc_value = 0;
            uint32_t timeout = 0;

            while (timeout < 1000) {
                adc_value = pins[j]->get_raw_adc(pins[j]);
                if (adc_value > 2700) {
                    float time_seconds = timeout / 1000.0f;
                    result.capacitance = time_seconds / 680.0f;
                    measured = true;
                    break;
                }
                timeout = get_tick_count() - start_time;
            }
        }
    }

    // Discharge capacitor
    _reset_pins(state);
    delay_ms(100);

    return result;
}

static void _reset_pins(tester_t* state) {
    pin_set_mode(&state->pin_A, PIN_TYPE_MIN_RESISTANT, PIN_MODE_PUSH_PULL_LOW);
    pin_set_mode(&state->pin_A, PIN_TYPE_MID_RESISTANT, PIN_MODE_PUSH_PULL_LOW);
    pin_set_mode(&state->pin_A, PIN_TYPE_MAX_RESISTANT, PIN_MODE_PUSH_PULL_LOW);

    pin_set_mode(&state->pin_B, PIN_TYPE_MIN_RESISTANT, PIN_MODE_PUSH_PULL_LOW);
    pin_set_mode(&state->pin_B, PIN_TYPE_MID_RESISTANT, PIN_MODE_PUSH_PULL_LOW);
    pin_set_mode(&state->pin_B, PIN_TYPE_MAX_RESISTANT, PIN_MODE_PUSH_PULL_LOW);

    pin_set_mode(&state->pin_C, PIN_TYPE_MIN_RESISTANT, PIN_MODE_PUSH_PULL_LOW);
    pin_set_mode(&state->pin_C, PIN_TYPE_MID_RESISTANT, PIN_MODE_PUSH_PULL_LOW);
    pin_set_mode(&state->pin_C, PIN_TYPE_MAX_RESISTANT, PIN_MODE_PUSH_PULL_LOW);
}

static void _prepare_pins(tester_t* state) {
    pin_set_mode(&state->pin_A, PIN_TYPE_MIN_RESISTANT, PIN_MODE_OPEN_DRAIN_HIGH);
    pin_set_mode(&state->pin_A, PIN_TYPE_MID_RESISTANT, PIN_MODE_OPEN_DRAIN_HIGH);
    pin_set_mode(&state->pin_A, PIN_TYPE_MAX_RESISTANT, PIN_MODE_OPEN_DRAIN_HIGH);

    pin_set_mode(&state->pin_B, PIN_TYPE_MIN_RESISTANT, PIN_MODE_OPEN_DRAIN_HIGH);
    pin_set_mode(&state->pin_B, PIN_TYPE_MID_RESISTANT, PIN_MODE_OPEN_DRAIN_HIGH);
    pin_set_mode(&state->pin_B, PIN_TYPE_MAX_RESISTANT, PIN_MODE_OPEN_DRAIN_HIGH);

    pin_set_mode(&state->pin_C, PIN_TYPE_MIN_RESISTANT, PIN_MODE_OPEN_DRAIN_HIGH);
    pin_set_mode(&state->pin_C, PIN_TYPE_MID_RESISTANT, PIN_MODE_OPEN_DRAIN_HIGH);
    pin_set_mode(&state->pin_C, PIN_TYPE_MAX_RESISTANT, PIN_MODE_OPEN_DRAIN_HIGH);
}

static float _measure_resistance(tester_t* state, pin_t* drive_pin, pin_t* measure_pin) {
    // First try with MID_RESISTANT (680Ω) for low resistance measurement
    pin_set_mode(drive_pin, PIN_TYPE_MID_RESISTANT, PIN_MODE_PUSH_PULL_HIGH);
    pin_set_mode(measure_pin, PIN_TYPE_MID_RESISTANT, PIN_MODE_OPEN_DRAIN_LOW);
    delay_ms(10);  // Allow stabilization

    uint16_t adc_value = measure_pin->get_raw_adc(measure_pin);
    float resistance = _calculate_resistance(adc_value, 680.0f);

    // If we got near-zero or invalid reading with MID_RESISTANT, try MAX_RESISTANT (470kΩ)
    if (resistance > 500.0f || resistance < 1.0f) {  // 680Ω * 0.75 ~= 500Ω
        pin_set_mode(drive_pin, PIN_TYPE_MAX_RESISTANT, PIN_MODE_PUSH_PULL_HIGH);
        pin_set_mode(measure_pin, PIN_TYPE_MAX_RESISTANT, PIN_MODE_OPEN_DRAIN_LOW);
        delay_ms(10);  // Allow stabilization

        adc_value = measure_pin->get_raw_adc(measure_pin);
        resistance = _calculate_resistance(adc_value, 470000.0f);
    }

    return resistance;
}

static float _calculate_resistance(uint16_t adc_value, float reference_resistor) {
    const float max_adc = 4095.0f;  // 12-bit ADC
    const float Vcc = 3.3f;         // Assuming 3.3V supply

    if (adc_value == 0)
        return INFINITY;  // Open circuit
    if (adc_value >= max_adc)
        return 0.0f;  // Short circuit

    float Vout = (adc_value / max_adc) * Vcc;
    float R_unknown = reference_resistor * (Vcc / Vout - 1.0f);

    return R_unknown;
}
