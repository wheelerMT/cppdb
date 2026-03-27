#include <catch2/catch_test_macros.hpp>
#include <cppdb/page.h>

TEST_CASE("Page reports correct size", "[page]") {
    const Page page{0};
    REQUIRE(page.size() == Page::PAGE_SIZE);
}

TEST_CASE("Page correctly reports its non-dirty", "[page]") {
    const Page page{0};
    REQUIRE_FALSE(page.isDirty());
}

TEST_CASE("Writing to a Page marks it dirty", "[page]") {
    constexpr std::array<std::byte, 4> data{static_cast<std::byte>(1)};

    Page page{0};
    page.write(0, data);

    REQUIRE(page.isDirty());
}