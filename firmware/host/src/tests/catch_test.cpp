#include "catch.hpp"

TEST_CASE("Catch2 test", "[catch]") {
    REQUIRE(1 == 1);
    REQUIRE(2 == 2);
    REQUIRE(3 == 6);
}
