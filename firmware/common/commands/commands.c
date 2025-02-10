
#include "commands.h"

#include <stdio.h>

#include "console.h"
#include "version.h"

static void _help_func(console_t* state, char* command_line, uint16_t arg_shifts[], uint8_t nargs);
static void _version_func(console_t* state, char* command_line, uint16_t arg_shifts[], uint8_t nargs);

extern void leds_func(console_t* state, char* command_line, uint16_t arg_shifts[], uint8_t nargs);

command_t commands_list[] = {
    {
        .name = "help",
        .description = "print all commands and its description or one. `help [command_name]`",
        .handler = _help_func,
    },
    {
        .name = "version",
        .description = "print version of software. `version`",
        .handler = _version_func,
    },
    {
        .name = "leds",
        .description = "print status, on/off leds. `led red[/green/blue] [on/off]`",
        .handler = leds_func,
    },
};

static void _help_func(console_t* state, char* command_line, uint16_t arg_shifts[], uint8_t nargs) {
    if (nargs == 1) {
        state->write("help:\r\n");
        for (uint16_t i = 0; i < state->nums_command; ++i) {
            sprintf(console_tx_buffer, " > %s - %s\n\r", state->commands[i].name, state->commands[i].description);
            state->write(console_tx_buffer);
        }
    } else if (nargs == 2) {
        command_t* command = console_find_command(state, &command_line[arg_shifts[1]]);
        if (command == NULL) {
            state->write("Unknown command\r\n");
            return;
        }
        sprintf(console_tx_buffer, " > %s - %s\n\r", command->name, command->description);

        state->write(console_tx_buffer);

    } else {
        state->write("Arguments error\r\n");
        return;
    }
}

static void _version_func(console_t* state, char* command_line, uint16_t arg_shifts[], uint8_t nargs) {
    (void)state;
    (void)command_line;
    (void)nargs;
    (void)arg_shifts;

    state->write(VERSION);
}
