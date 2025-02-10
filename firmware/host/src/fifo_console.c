#include "fifo_console.h"

#include <stdio.h>
#include <string.h>
#include <sys/fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

#include "commands.h"

static int _rx_fifo = -1;
static int _tx_fifo = -1;
static bool _cout = true;

static uint16_t _read_func(char* buffer) { return read(_rx_fifo, buffer, CONSOLE_MAX_COMMAND_SIZE); }
static void _write_func(char* buffer) {
    if (_tx_fifo < 0) return;

    write(_tx_fifo, buffer, strlen(buffer));
    if (_cout) { printf("%s", buffer); }
}

void fifo_console_init(console_t* state, bool cout) {
    mkfifo(FIFO_CONSOLE_TX_FILENAME, 0777);
    mkfifo(FIFO_CONSOLE_RX_FILENAME, 0777);

    _rx_fifo = open(FIFO_CONSOLE_RX_FILENAME, O_RDONLY | O_NONBLOCK);
    _tx_fifo = open(FIFO_CONSOLE_TX_FILENAME, O_RDWR | O_NONBLOCK);
    _cout = cout;

    console_init(state, commands_list, NUM_COMMANDS, _read_func, _write_func);
}

void fifo_console_process(console_t* state) { console_process(state); }

void fifo_console_deinit(console_t* state) {
    (void)state;
    close(_tx_fifo);
    close(_rx_fifo);
}