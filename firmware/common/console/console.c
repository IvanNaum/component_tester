#include "console.h"

#include <stdio.h>
#include <string.h>

#include "stdint.h"

static command_t* _find_command(console_t* state, char* command_name);

void console_init(
    console_t* state, command_t* commands, uint16_t nums_command, console_read_func_t read_func,
    console_write_func_t write_func
) {
    state->commands = commands;
    state->nums_command = nums_command;
    state->read = read_func;
    state->write = write_func;
}

void console_process(console_t* state) {
    uint16_t command_line_len = 0;
    uint16_t arg_shift[CONSOLE_MAX_COMMAND_ARGS] = {0};  // [0] - command name, next - args
    static uint8_t nargs = 0;
    static char command_line[CONSOLE_MAX_COMMAND_SIZE];
    static char rx_line[CONSOLE_MAX_COMMAND_SIZE];

    uint16_t count = state->read(rx_line);
    if (0 == count) return;

    for (uint16_t i = 0; i < count; i++) {
        // TODO: add buffer overflow error handling
        command_line[command_line_len++] = rx_line[i];
        if (rx_line[i] == ' ') {
            command_line[command_line_len - 1] = '\0';
            continue;
        } else if (rx_line[i] == '\r' || rx_line[i] == '\n') {
            command_line[command_line_len - 1] = '\0';
            command_t* command = _find_command(state, &command_line[arg_shift[0]]);
            command->handler(state, command_line, arg_shift, nargs);

            nargs = 0;
            command_line_len = 0;

            break;  // TODO: impl args reading
        } else {
            // TODO: Add arg
        }
    }
}

static command_t* _find_command(console_t* state, char* command_name) {
    for (uint16_t i = 0; i < state->nums_command; ++i) {
        if (strcmp(state->commands[i].name, command_name) == 0) { return &state->commands[i]; }
    }
    return NULL;
}
