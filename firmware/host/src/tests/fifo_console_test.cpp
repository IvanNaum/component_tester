#include "fifo_console.h"

#include <sys/fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

#include "catch.hpp"
#include "version.h"

TEST_CASE("Console init", "[console][version_command]") {
    console_t console;
    fifo_console_init(&console, false);

    int tx_fifo = open(FIFO_CONSOLE_RX_FILENAME, O_WRONLY | O_NONBLOCK);
    int rx_fifo = open(FIFO_CONSOLE_TX_FILENAME, O_RDONLY | O_NONBLOCK);

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
    close(tx_fifo);
    close(rx_fifo);
}

TEST_CASE("Unknown command", "[console][unknown]") {
    console_t console;
    fifo_console_init(&console, false);

    int tx_fifo = open(FIFO_CONSOLE_RX_FILENAME, O_WRONLY | O_NONBLOCK);
    int rx_fifo = open(FIFO_CONSOLE_TX_FILENAME, O_RDONLY | O_NONBLOCK);

    const char* command = "noisrev\r\n";
    write(tx_fifo, command, strlen(command));
    fifo_console_process(&console);

    char result[CONSOLE_MAX_OUTPUT_SIZE];
    int res_len = read(rx_fifo, result, CONSOLE_MAX_OUTPUT_SIZE);

    SECTION("VALID") {
        REQUIRE(res_len > 0);
        REQUIRE(strstr(result, CONSOLE_UNKNOWN_COMMAND_ERROR));
    }

    fifo_console_deinit(&console);
    close(tx_fifo);
    close(rx_fifo);
}

TEST_CASE("Unblock console", "[console][version_command][unblock]") {
    console_t console;
    fifo_console_init(&console, false);

    int tx_fifo = open(FIFO_CONSOLE_RX_FILENAME, O_WRONLY | O_NONBLOCK);
    int rx_fifo = open(FIFO_CONSOLE_TX_FILENAME, O_RDONLY | O_NONBLOCK);

    const char* command1 = "  ver";
    write(tx_fifo, command1, strlen(command1));
    fifo_console_process(&console);

    const char* command2 = "sion   \r\n";
    write(tx_fifo, command2, strlen(command2));
    fifo_console_process(&console);

    char result[CONSOLE_MAX_OUTPUT_SIZE];
    int res_len = read(rx_fifo, result, CONSOLE_MAX_OUTPUT_SIZE);

    SECTION("VALID") {
        REQUIRE(res_len > 0);
        REQUIRE(strstr(result, VERSION));
    }

    fifo_console_deinit(&console);
    close(tx_fifo);
    close(rx_fifo);
}

TEST_CASE("Overflow input buffer", "[console][overflow]") {
    console_t console;
    fifo_console_init(&console, false);

    int tx_fifo = open(FIFO_CONSOLE_RX_FILENAME, O_WRONLY | O_NONBLOCK);
    int rx_fifo = open(FIFO_CONSOLE_TX_FILENAME, O_RDONLY | O_NONBLOCK);

    auto str_command = std::string(CONSOLE_MAX_COMMAND_SIZE + 1, '*');
    str_command += "\r\n";
    const char* command1 = str_command.c_str();
    write(tx_fifo, command1, strlen(command1));
    fifo_console_process(&console);

    char result[CONSOLE_MAX_OUTPUT_SIZE];
    int res_len = read(rx_fifo, result, CONSOLE_MAX_OUTPUT_SIZE);

    REQUIRE(res_len > 0);
    REQUIRE(strstr(result, CONSOLE_OVERFLOW_BUFFER_ERROR));

    const char* command2 = "version\r\n";
    write(tx_fifo, command2, strlen(command2));
    fifo_console_process(&console);

    res_len = read(rx_fifo, result, CONSOLE_MAX_OUTPUT_SIZE);

    SECTION("VALID") {
        REQUIRE(res_len > 0);
        REQUIRE(strstr(result, VERSION));
    }

    fifo_console_deinit(&console);
    close(tx_fifo);
    close(rx_fifo);
}

TEST_CASE("Overflow args buffer", "[console][overflow]") {
    console_t console;
    fifo_console_init(&console, false);

    int tx_fifo = open(FIFO_CONSOLE_RX_FILENAME, O_WRONLY | O_NONBLOCK);
    int rx_fifo = open(FIFO_CONSOLE_TX_FILENAME, O_RDONLY | O_NONBLOCK);

    std::string str_command = "version";

    // First arguments is command name
    for (int i = 0; i < CONSOLE_MAX_COMMAND_ARGS; ++i) { str_command += " a"; }
    str_command += "\r\n";

    const char* command = str_command.c_str();

    write(tx_fifo, command, strlen(command));
    fifo_console_process(&console);

    char result[CONSOLE_MAX_OUTPUT_SIZE];
    int res_len = read(rx_fifo, result, CONSOLE_MAX_OUTPUT_SIZE);

    SECTION("VALID") {
        REQUIRE(res_len > 0);
        REQUIRE(strstr(result, CONSOLE_OVERFLOW_ARGS_ERROR));
    }

    fifo_console_deinit(&console);
    close(tx_fifo);
    close(rx_fifo);
}
