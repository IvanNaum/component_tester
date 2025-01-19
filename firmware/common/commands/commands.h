/**
 * Commands module
 */

#ifndef _COMMANDS_H
#define _COMMANDS_H

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

command_t commands_list[NUM_COMMANDS];

#ifdef __cplusplus
}
#endif

#endif  // _COMMANDS_H