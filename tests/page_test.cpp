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
        constexpr std::array<std::byte, 4> data{};

        auto success = page.write(0, data);
        REQUIRE(success.has_value());
        REQUIRE(page.isDirty());
    }

    SECTION("data can be read back") {
        constexpr std::array writeData{std::byte{1}, std::byte{2}, std::byte{3}, std::byte{4}};

        const auto success = page.write(0, writeData);
        const auto readData = page.read(0, writeData.size());

        REQUIRE(readData.has_value());
        REQUIRE(std::ranges::equal(readData.value(), writeData));
    }

    SECTION("data can be correctly written to a non-zero offset") {
        constexpr std::array initialData{std::byte{1}, std::byte{2}, std::byte{3}, std::byte{4}};
        constexpr std::array offsetData{std::byte{10}, std::byte{20}, std::byte{30}, std::byte{40}};

        const auto initialResult = page.write(0, initialData);
        const auto offsetResult = page.write(8, offsetData);
        REQUIRE(initialResult.has_value());
        REQUIRE(offsetResult.has_value());

        const auto initialReadData = page.read(0, 4);
        const auto offsetReadData = page.read(8, 4);

        REQUIRE(initialReadData.has_value());
        REQUIRE(offsetReadData.has_value());
        REQUIRE(std::ranges::equal(initialData, initialReadData.value()));
        REQUIRE(std::ranges::equal(offsetData, offsetReadData.value()));
    }
}
