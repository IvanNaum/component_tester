/**
 * Fifo console implementation
 */

#ifndef _FIFO_CONSOLE_H
#define _FIFO_CONSOLE_H

#ifdef __cplusplus
extern "C" {
#endif

#include "console.h"

extern command_t commands_list[];

#define FIFO_CONSOLE_RX_FILENAME "fifo_console_rx"  // Receive for console, transmit for user
#define FIFO_CONSOLE_TX_FILENAME "fifo_console_tx"  // Transmit for console, receive for user

void fifo_console_init(console_t* state);
void fifo_console_process(console_t* state);
void fifo_console_deinit(console_t* state);

#ifdef __cplusplus
}
#endif

#endif  // _FIFO_CONSOLE_H