#include <algorithm>
#include <array>
#include <catch2/catch_test_macros.hpp>
#include <cppdb/page.h>

TEST_CASE("Upon Page creation", "[page]") {
    const Page page{0};

    SECTION("reports correct size") {
        REQUIRE(page.size() == Page::PAGE_SIZE);
    }

    SECTION("correctly reports its non-dirty") {
        REQUIRE_FALSE(page.isDirty());
    }
}

TEST_CASE("Page can be written to and read from", "[page]") {
    Page page{0};

    SECTION("write marks it dirty") {
        constexpr std::array<std::byte, 4> data{std::byte{1}};

        page.write(0, data);

        REQUIRE(page.isDirty());
    }

    SECTION("data can be read back") {
        constexpr std::array writeData{std::byte{1}, std::byte{2}, std::byte{3}, std::byte{4}};

        page.write(0, writeData);
        auto readData = page.read(0, writeData.size());

        REQUIRE(std::ranges::equal(readData, writeData));
    }

    SECTION("data can be correctly written to a non-zero offset") {
        constexpr std::array initialData{std::byte{1}, std::byte{2}, std::byte{3}, std::byte{4}};
        constexpr std::array offsetData{std::byte{10}, std::byte{20}, std::byte{30}, std::byte{40}};

        page.write(0, initialData);
        page.write(8, offsetData);

        const auto initialReadData = page.read(0, 4);
        const auto offsetReadData = page.read(8, 4);

        REQUIRE(std::ranges::equal(initialData, initialReadData));
        REQUIRE(std::ranges::equal(offsetData, offsetReadData));
    }
}
