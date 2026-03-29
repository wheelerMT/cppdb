#include "cppdb/disk_manager.h"

#include <catch2/catch_test_macros.hpp>
#include <filesystem>

struct DiskManagerFixture {
    std::filesystem::path testFilePath{std::filesystem::temp_directory_path() / "test.cppdb"};

    ~DiskManagerFixture() { std::filesystem::remove(testFilePath); }
};

TEST_CASE_METHOD(DiskManagerFixture, "DiskManager can be created", "[disk_manager]") {
    const DiskManager manager{testFilePath};

    SECTION("file exists after creation") {
        REQUIRE(std::filesystem::exists(testFilePath));
    }

    SECTION("page count is zero for a new file") {
        REQUIRE(manager.pageCount() == 0);
    }
}