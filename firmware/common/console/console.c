#include "console.h"

#include <stdio.h>
#include <string.h>

#include "stdbool.h"
#include "stdint.h"

char console_tx_buffer[CONSOLE_MAX_OUTPUT_SIZE];

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
    static uint16_t command_line_len = 0;
    static uint8_t nargs = 0;
    static uint16_t arg_shift[CONSOLE_MAX_COMMAND_ARGS] = {0};  // [0] - command name, next - args
    static char command_line[CONSOLE_MAX_COMMAND_SIZE];
    static char rx_line[CONSOLE_MAX_COMMAND_SIZE];
    static bool last_space = true;

    uint16_t count = state->read(rx_line);
    if (0 == count) return;

    for (uint16_t i = 0; i < count; i++) {
        command_line[command_line_len++] = rx_line[i];
        if (rx_line[i] == ' ' || rx_line[i] == '\r') {
            command_line[command_line_len - 1] = '\0';
            last_space = true;
        } else if (rx_line[i] == '\n' && command_line_len > 1) {
            command_line[command_line_len - 1] = '\0';
            command_t* command = console_find_command(state, &command_line[arg_shift[0]]);
            if (command == NULL) {
                state->write(CONSOLE_UNKNOWN_COMMAND_ERROR);
            } else {
                command->handler(state, command_line, arg_shift, nargs);
            }
            nargs = 0;
            command_line_len = 0;
            last_space = true;
            continue;
        } else if (last_space) {
            arg_shift[nargs++] = command_line_len - 1;
            last_space = false;
        }
        if (command_line_len == CONSOLE_MAX_COMMAND_SIZE) {
            state->write(CONSOLE_OVERFLOW_BUFFER_ERROR);
            nargs = 0;
            command_line_len = 0;
            last_space = true;
            break;
        }
        if (nargs == CONSOLE_MAX_COMMAND_ARGS) {
            state->write(CONSOLE_OVERFLOW_ARGS_ERROR);
            nargs = 0;
            command_line_len = 0;
            last_space = true;
            break;
        }
    }
}

command_t* console_find_command(console_t* state, char* command_name) {
    for (uint16_t i = 0; i < state->nums_command; ++i) {
        if (strcmp(state->commands[i].name, command_name) == 0) { return &state->commands[i]; }
    }
    return NULL;
}
