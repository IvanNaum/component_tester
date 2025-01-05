#include <iostream>

extern "C" {
#include "log.h"
}

int main() {
    log_info("Success!");

    return 0;
}