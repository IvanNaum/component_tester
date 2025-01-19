#include "fifo_console.h"

#include <stdio.h>
#include <string.h>
#include <sys/fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

#include "commands.h"

static uint16_t _read_func(char* buffer) { return read(fifo_console_tx, buffer, sizeof(buffer)); }
static void _write_func(char* buffer) { write(fifo_console_rx, buffer, strlen(buffer)); }  // TODO: add printf mode

void fifo_console_init(console_t* state) {
    // TODO: refactoring tx and rx
    mkfifo(FIFO_CONSOLE_TX_FILENAME, 0777);
    mkfifo(FIFO_CONSOLE_RX_FILENAME, 0777);

    fifo_console_tx = open(FIFO_CONSOLE_TX_FILENAME, O_RDWR | O_NONBLOCK);
    fifo_console_rx = open(FIFO_CONSOLE_RX_FILENAME, O_RDWR | O_NONBLOCK);

    console_init(state, commands_list, NUM_COMMANDS, _read_func, _write_func);
}

void fifo_console_process(console_t* state) { console_process(state); }

void fifo_console_deinit(console_t* state) {
    (void)state;
    close(fifo_console_tx);
    close(fifo_console_rx);
}