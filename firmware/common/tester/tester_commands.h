#ifndef TESTER_COMMANDS_H
#define TESTER_COMMANDS_H

#include "console.h"

void tester_test_command_handler(console_t* state, char* command_line, uint16_t arg_shifts[], uint8_t nargs);
void tester_test_transistor_command_handler(console_t* state, char* command_line, uint16_t arg_shifts[], uint8_t nargs);
void tester_test_diode_command_handler(console_t* state, char* command_line, uint16_t arg_shifts[], uint8_t nargs);
void tester_test_resistor_command_handler(console_t* state, char* command_line, uint16_t arg_shifts[], uint8_t nargs);
void tester_test_capacitor_command_handler(console_t* state, char* command_line, uint16_t arg_shifts[], uint8_t nargs);

#endif  // TESTER_COMMANDS_H
