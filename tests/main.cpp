#include <catch2/catch_test_macros.hpp>

TEST_CASE("Verify Catch2", "[smoke]") {
    SECTION("smoke test") {
        // arrange
        // act
        // assert
        REQUIRE(1 + 1 == 2);
    }
}