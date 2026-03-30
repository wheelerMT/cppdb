#include "cppdb/disk_manager.h"

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
    } // manager destroyed here -- file is closed and flushed

    // Reopen the same file
    auto reopened = *DiskManager::open(testFilePath);
    REQUIRE(reopened.pageCount() == 2);
}