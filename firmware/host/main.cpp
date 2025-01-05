#include <iostream>

#define CATCH_CONFIG_RUNNER
#include "catch.hpp"

extern "C" {
#include "log.h"
}

#define LOG_DEFAULT_LEVEL LOG_DEBUG

int main(int argc, char** argv) {
    log_set_level(LOG_DEFAULT_LEVEL);

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
    return 0;
#else
    // Tests runner
    int result = Catch::Session().run(argc, argv);
    return result;
#endif  // DEBUG_MODE
}