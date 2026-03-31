#include "cppdb/disk_manager.h"
#include "cppdb/page.h"

#include <algorithm>
#include <catch2/catch_test_macros.hpp>
#include <filesystem>

struct DiskManagerFixture {
    std::filesystem::path testFilePath{std::filesystem::temp_directory_path() / "test.cppdb"};
    DiskManager manager = *DiskManager::open(testFilePath);
    ~DiskManagerFixture() { std::filesystem::remove(testFilePath); }
};

TEST_CASE_METHOD(DiskManagerFixture, "DiskManager can be created", "[disk_manager]") {

    SECTION("file exists after creation") {
        REQUIRE(std::filesystem::exists(testFilePath));
    }

    SECTION("page count is zero for a new file") {
        REQUIRE(manager.pageCount() == 0);
    }
}

TEST_CASE_METHOD(DiskManagerFixture, "DiskManager allocation", "[disk_manager]") {

    SECTION("allocatePage returns ID 0 for the first page") {
        const auto result = manager.allocatePage();
        REQUIRE(result.has_value());
        REQUIRE(result.value() == 0);
    }

    SECTION("pageCount returns 1 after first allocation") {
        auto result = manager.allocatePage();
        REQUIRE(result.has_value());
        REQUIRE(manager.pageCount() == 1);
    }
}

TEST_CASE_METHOD(DiskManagerFixture, "DiskManager persists page count", "[disk_manager]") {
    {
        auto result = manager.allocatePage();
        REQUIRE(result.has_value());
        result = manager.allocatePage();
        REQUIRE(result.has_value());
    }

    // Reopen the same file
    auto reopened = *DiskManager::open(testFilePath);
    REQUIRE(reopened.pageCount() == 2);
}

TEST_CASE_METHOD(DiskManagerFixture, "DiskManager can read and write a page", "[disk_manager]") {
    const auto result = manager.allocatePage();
    REQUIRE(result.has_value());
    const auto pageId = result.value();

    Page page{pageId};
    constexpr std::array writeData{std::byte{1}, std::byte{2}, std::byte{3}, std::byte{4}};
    const auto writeResult = page.write(0, writeData);
    REQUIRE(writeResult.has_value());

    SECTION("can write a page successfully") {
        auto diskWriteResult = manager.writePage(pageId, page);
        REQUIRE(diskWriteResult.has_value());
    }

    SECTION("can read a page successfully") {
        auto diskWriteResult = manager.writePage(pageId, page);
        REQUIRE(diskWriteResult.has_value());

        Page newPage{1};
        auto diskReadResult = manager.readPage(pageId, newPage);
        REQUIRE(diskReadResult.has_value());
        REQUIRE(std::ranges::equal(page.rawData(), newPage.rawData()));
    }

    SECTION("persistence round-trip") {
        {
            auto diskWriteResult = manager.writePage(pageId, page);
            REQUIRE(diskWriteResult.has_value());
        }

        // Reopen the same file
        auto reopened = *DiskManager::open(testFilePath);
        Page newPage{1};
        auto diskReadResult = reopened.readPage(pageId, newPage);
        REQUIRE(diskReadResult.has_value());
        REQUIRE(std::ranges::equal(page.rawData(), newPage.rawData()));
    }
}