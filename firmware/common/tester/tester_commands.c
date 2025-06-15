#include "tester_commands.h"

#include <string.h>

#include "tester.h"

extern tester_t tester_status;
extern char console_tx_buffer[CONSOLE_MAX_OUTPUT_SIZE];

void tester_test_command_handler(console_t* state, char* command_line, uint16_t arg_shifts[], uint8_t nargs) {
    component_t component;
    component_init(&component);
    if (nargs == 1) {
        component = tester_test(&tester_status);
    } else if (nargs != 2) {
        const char* component_type_str = &command_line[arg_shifts[1]];

        if (strcmp(component_type_str, "tran") == 0) {
            component = tester_test_transistor(&tester_status);
        } else if (strcmp(component_type_str, "diode") == 0) {
            component = tester_test_diode(&tester_status);
        } else if (strcmp(component_type_str, "resistor") == 0) {
            component = tester_test_resistor(&tester_status);
        } else if (strcmp(component_type_str, "cap") == 0) {
            component = tester_test_capacitor(&tester_status);
        } else {
            state->write("Unknown component\r\n");
            return;
        }
    } else {
        state->write("Arguments error\r\n");
        return;
    }

    component_to_str(&component, console_tx_buffer);

    state->write(console_tx_buffer);
}
