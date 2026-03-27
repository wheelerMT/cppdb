#include <algorithm>
#include <array>
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

TEST_CASE("Data written to a Page can be read back", "[page]") {
    constexpr std::array<std::byte, 4> writeData{
        static_cast<std::byte>(1), static_cast<std::byte>(2), static_cast<std::byte>(3),
        static_cast<std::byte>(4)};
    Page page{0};

    page.write(0, writeData);
    auto readData = page.read(0, writeData.size());

    REQUIRE(std::ranges::equal(readData, writeData));
}