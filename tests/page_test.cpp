#include <catch2/catch_test_macros.hpp>
#include <cppdb/page.h>

TEST_CASE("Page reports correct size", "[page]") {
    const Page page{0};
    REQUIRE(page.size() == Page::PAGE_SIZE);
}

TEST_CASE("Page correctly reports its non-dirty", "[page]") {
    const Page page{0};
    REQUIRE(page.isDirty() == false);
}