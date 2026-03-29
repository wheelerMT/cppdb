#include "cppdb/disk_manager.h"

#include <catch2/catch_test_macros.hpp>
#include <filesystem>

struct DiskManagerFixture {
    std::filesystem::path testFilePath{std::filesystem::temp_directory_path() / "test.cppdb"};

    ~DiskManagerFixture() { std::filesystem::remove(testFilePath); }
};

TEST_CASE_METHOD(DiskManagerFixture, "DiskManager can be created with a new file path",
                 "[disk_manager]") {
    DiskManager manager{testFilePath};

    REQUIRE(std::filesystem::exists(testFilePath));
}