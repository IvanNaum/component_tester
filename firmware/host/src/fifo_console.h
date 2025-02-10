/**
 * Fifo console implementation
 */

#ifndef FIFO_CONSOLE_H
#define FIFO_CONSOLE_H

#ifdef __cplusplus
extern "C" {
#endif

#include "console.h"
#include "stdbool.h"

extern command_t commands_list[];

#define FIFO_CONSOLE_RX_FILENAME "fifo_console_rx"  // Receive for console, transmit for user
#define FIFO_CONSOLE_TX_FILENAME "fifo_console_tx"  // Transmit for console, receive for user

void fifo_console_init(console_t* state, bool cout);
void fifo_console_process(console_t* state);
void fifo_console_deinit(console_t* state);

#ifdef __cplusplus
}
#endif

#endif  // FIFO_CONSOLE_H
