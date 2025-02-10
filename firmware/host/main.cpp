#define CATCH_CONFIG_RUNNER

#include <iostream>

#include "console.h"
#include "leds.h"

#ifdef DEBUG_MODE
#include <unistd.h>

#include "fifo_console.h"
#else
#endif  // DEBUG_MODE
#include "catch.hpp"

extern "C" {
#include "log.h"
}

leds_t leds;

#define LOG_DEFAULT_LEVEL LOG_DEBUG

int main(int argc, char** argv) {
    log_set_level(LOG_DEFAULT_LEVEL);
    // leds_init(&leds);

#ifdef DEBUG_MODE
    // Arbitrary code for debug modules
    (void)argc;
    (void)argv;

    log_trace("trace");
    log_debug("debug");
    log_info("info");
    log_warn("warn");
    log_error("error");
    log_fatal("fatal");

    console_t console;
    fifo_console_init(&console, true);

    while (1) {
        fifo_console_process(&console);
        usleep(100);
    }

    fifo_console_deinit(&console);

    return 0;
#else
    // Tests runner
    int result = Catch::Session().run(argc, argv);
    return result;
#endif  // DEBUG_MODE
}