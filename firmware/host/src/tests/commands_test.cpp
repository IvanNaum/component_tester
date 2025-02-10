#include "commands.h"

#include <sys/fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

#include "catch.hpp"
#include "fifo_console.h"
#include "version.h"

TEST_CASE("Help command", "[console][help_command]") {
    console_t console;
    fifo_console_init(&console);

    int tx_fifo = open(FIFO_CONSOLE_RX_FILENAME, O_WRONLY | O_NONBLOCK);
    int rx_fifo = open(FIFO_CONSOLE_TX_FILENAME, O_RDONLY | O_NONBLOCK);

    const char* command = "help\r\n";

    write(tx_fifo, command, strlen(command));
    fifo_console_process(&console);

    char result[CONSOLE_MAX_OUTPUT_SIZE];
    int res_len = read(rx_fifo, result, CONSOLE_MAX_OUTPUT_SIZE);

    SECTION("VALID") {
        REQUIRE(res_len > 0);
        REQUIRE(strstr(result, "help"));
        for (auto i = 0; i < NUM_COMMANDS; ++i) { REQUIRE(strstr(result, commands_list[i].name)); }
    }

    fifo_console_deinit(&console);
    close(tx_fifo);
    close(rx_fifo);
}

TEST_CASE("Help version command ", "[console][help_command]") {
    console_t console;
    fifo_console_init(&console);

    int tx_fifo = open(FIFO_CONSOLE_RX_FILENAME, O_WRONLY | O_NONBLOCK);
    int rx_fifo = open(FIFO_CONSOLE_TX_FILENAME, O_RDONLY | O_NONBLOCK);

    const char* command = "help version\r\n";

    write(tx_fifo, command, strlen(command));
    fifo_console_process(&console);

    char result[CONSOLE_MAX_OUTPUT_SIZE];
    int res_len = read(rx_fifo, result, CONSOLE_MAX_OUTPUT_SIZE);

    SECTION("VALID") {
        REQUIRE(res_len > 0);
        // REQUIRE(strstr(result, "help"));

        REQUIRE(strstr(result, commands_list[COMMAND_VERSION].name));
        REQUIRE(strstr(result, commands_list[COMMAND_VERSION].description));

        for (auto i = 0; i < NUM_COMMANDS; ++i) {
            if (i == COMMAND_VERSION) { continue; }
            REQUIRE(!strstr(result, commands_list[i].name));
        }
    }

    fifo_console_deinit(&console);
    close(tx_fifo);
    close(rx_fifo);
}

TEST_CASE("Version command", "[console][version_command]") {
    console_t console;
    fifo_console_init(&console);

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

TEST_CASE("Leds command errors", "[console][leds_command]") {
    console_t console;
    fifo_console_init(&console);

    int tx_fifo = open(FIFO_CONSOLE_RX_FILENAME, O_WRONLY | O_NONBLOCK);
    int rx_fifo = open(FIFO_CONSOLE_TX_FILENAME, O_RDONLY | O_NONBLOCK);

    const char* command = "leds\r\n";

    write(tx_fifo, command, strlen(command));
    fifo_console_process(&console);

    char result[CONSOLE_MAX_OUTPUT_SIZE];
    int res_len = read(rx_fifo, result, CONSOLE_MAX_OUTPUT_SIZE);

    SECTION("VALID") {
        REQUIRE(res_len > 0);
        REQUIRE(strstr(result, "Arguments error"));
    }

    command = "leds a a a\r\n";

    write(tx_fifo, command, strlen(command));
    fifo_console_process(&console);

    res_len = read(rx_fifo, result, CONSOLE_MAX_OUTPUT_SIZE);

    SECTION("VALID") {
        REQUIRE(res_len > 0);
        REQUIRE(strstr(result, "Arguments error"));
    }

    fifo_console_deinit(&console);
    close(tx_fifo);
    close(rx_fifo);
}

TEST_CASE("Leds command", "[console][leds_command]") {
    console_t console;
    fifo_console_init(&console);

    int tx_fifo = open(FIFO_CONSOLE_RX_FILENAME, O_WRONLY | O_NONBLOCK);
    int rx_fifo = open(FIFO_CONSOLE_TX_FILENAME, O_RDONLY | O_NONBLOCK);

    const char* command1 = "leds green\r\n";

    write(tx_fifo, command1, strlen(command1));
    fifo_console_process(&console);

    char result[CONSOLE_MAX_OUTPUT_SIZE];
    int res_len = read(rx_fifo, result, CONSOLE_MAX_OUTPUT_SIZE);

    SECTION("VALID") {
        REQUIRE(res_len > 0);
        REQUIRE(strstr(result, "green"));
        REQUIRE(strstr(result, "0"));
    }

    const char* command2 = "leds green on\r\n";

    write(tx_fifo, command2, strlen(command2));
    fifo_console_process(&console);

    res_len = read(rx_fifo, result, CONSOLE_MAX_OUTPUT_SIZE);

    SECTION("VALID") {
        REQUIRE(res_len > 0);
        REQUIRE(strstr(result, "green"));
        REQUIRE(!strstr(result, "0"));
    }

    fifo_console_deinit(&console);
    close(tx_fifo);
    close(rx_fifo);
}
