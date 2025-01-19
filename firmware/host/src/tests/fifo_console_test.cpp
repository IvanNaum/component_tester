#include "fifo_console.h"

#include <sys/fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

#include "catch.hpp"
#include "version.h"

TEST_CASE("Console init", "[console][version]") {
    console_t console;
    fifo_console_init(&console);

    int tx_fifo = open(FIFO_CONSOLE_RX_FILENAME, O_WRONLY | O_NONBLOCK);
    int rx_fifo = open(FIFO_CONSOLE_TX_FILENAME, O_RDONLY | O_NONBLOCK);

    REQUIRE(tx_fifo > 0);
    REQUIRE(rx_fifo > 0);

    const char* command = "version\r\n";
    write(tx_fifo, command, strlen(command));
    fifo_console_process(&console);

    char result[CONSOLE_MAX_OUTPUT_SIZE];
    int res_len = read(rx_fifo, result, CONSOLE_MAX_OUTPUT_SIZE);

    SECTION("VALID") {
        REQUIRE(res_len > 0);
        REQUIRE(strstr(result, VERSION));
    }

    fifo_console_deinit(&console);
}

// TODO: add tests:
//  1. Buffer input overflow
//  2. Cutting input line (ex. "he", "lp\r\n") / Unblocking
//  3. Unknown commands
//  4. Find last/first command