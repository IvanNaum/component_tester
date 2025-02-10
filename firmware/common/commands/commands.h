/**
 * Commands module
 */

#ifndef COMMANDS_H
#define COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "console.h"

typedef enum commands {
    COMMAND_HELP,
    COMMAND_VERSION,
    COMMAND_LED,
    NUM_COMMANDS  // Number of commands, should be the last element
} commands_type_t;

extern command_t commands_list[NUM_COMMANDS];

#ifdef __cplusplus
}
#endif

#endif  // COMMANDS_H
