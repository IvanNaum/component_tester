#include "fifo_console.h"

#include <sys/fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

#include "catch.hpp"
#include "version.h"

TEST_CASE("Base console init", "[console][help]") {
    console_t console;
    fifo_console_init(&console);

    REQUIRE(fifo_console_tx > 0);
    REQUIRE(fifo_console_rx > 0);

    const char* command = "version\r\n";
    write(fifo_console_tx, command, strlen(command));
    fifo_console_process(&console);

    char result[CONSOLE_MAX_OUTPUT_SIZE];
    int res_len = read(fifo_console_rx, result, CONSOLE_MAX_OUTPUT_SIZE);

    // TODO add reading and REQUIRE
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