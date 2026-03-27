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
        constexpr std::array<std::byte, 4> data{static_cast<std::byte>(1)};

        page.write(0, data);

        REQUIRE(page.isDirty());
    }

    SECTION("data can be read back") {
        constexpr std::array writeData{static_cast<std::byte>(1), static_cast<std::byte>(2),
                                       static_cast<std::byte>(3), static_cast<std::byte>(4)};

        page.write(0, writeData);
        auto readData = page.read(0, writeData.size());

        REQUIRE(std::ranges::equal(readData, writeData));
    }
}
