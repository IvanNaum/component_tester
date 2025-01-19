/**
 * Console module
 */

#ifndef _CONSOLE_H
#define _CONSOLE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#define CONSOLE_MAX_COMMAND_SIZE (64)
#define CONSOLE_MAX_OUTPUT_SIZE (256)
#define CONSOLE_MAX_COMMAND_ARGS (6)

struct console;

typedef uint16_t (*console_read_func_t)(char* buffer);
typedef void (*console_write_func_t)(char* buffer);
typedef void (*command_handler_t)(struct console* state, char* command_line, uint16_t* arg_shifts, uint8_t nargs);

typedef struct console_command {
    const char* name;
    const char* description;
    command_handler_t handler;
} command_t;

typedef struct console {
    uint16_t nums_command;
    command_t* commands;
    console_read_func_t read;
    console_write_func_t write;
} console_t;

char console_tx_buffer[CONSOLE_MAX_OUTPUT_SIZE];

void console_init(
    console_t* state, command_t* commands, uint16_t nums_command, console_read_func_t read_func,
    console_write_func_t write_func
);
void console_process(console_t* state);

#ifdef __cplusplus
}
#endif

#endif  // _CONSOLE_H