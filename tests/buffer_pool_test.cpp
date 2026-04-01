#include "cppdb/buffer_pool.h"
#include "cppdb/disk_manager.h"

#include <catch2/catch_test_macros.hpp>

struct DiskManagerFixture {
    std::filesystem::path testFilePath{std::filesystem::temp_directory_path() / "test.cppdb"};
    DiskManager manager = *DiskManager::open(testFilePath);
    ~DiskManagerFixture() { std::filesystem::remove(testFilePath); }
};

TEST_CASE_METHOD(DiskManagerFixture, "buffer pool is created correctly", "[buffer_pool]") {
    constexpr std::size_t numFrames = 512;
    const BufferPool pool{std::move(manager), numFrames};
    REQUIRE(pool.numFrames() == numFrames);
}

TEST_CASE_METHOD(DiskManagerFixture, "buffer pool returns a valid page pointer and ID",
                 "[buffer_pool]") {
    constexpr std::size_t numFrames = 512;
    BufferPool pool{std::move(manager), numFrames};

    auto result = pool.newPage();
    REQUIRE(result.has_value());
    REQUIRE(result->page != nullptr);
    REQUIRE(result->pageId == 0);
}