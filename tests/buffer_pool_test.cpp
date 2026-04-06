#include "cppdb/buffer_pool.h"
#include "cppdb/disk_manager.h"

#include <algorithm>
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

TEST_CASE_METHOD(DiskManagerFixture, "buffer pool fetches a page already in cache",
                 "[buffer_pool]") {
    constexpr std::size_t numFrames = 512;
    BufferPool pool{std::move(manager), numFrames};
    auto result = pool.newPage();
    REQUIRE(result.has_value());
    const auto firstPage = result.value();

    auto fetchResult = pool.fetchPage(firstPage.pageId);
    REQUIRE(fetchResult.has_value());
    REQUIRE(fetchResult.value().pageId == firstPage.pageId);
}

TEST_CASE_METHOD(DiskManagerFixture, "buffer pool loads page into frame if it is not in cache",
                 "[buffer_pool]") {
    constexpr std::size_t numFrames = 512;
    constexpr std::array writeData{std::byte{1}, std::byte{2}, std::byte{3}, std::byte{4}};

    // Write a page directly via DiskManager — guaranteed on disk
    const auto pageId = *manager.allocatePage();
    Page page{pageId};
    REQUIRE(page.write(0, writeData).has_value());
    REQUIRE(manager.writePage(pageId, page).has_value());

    // Fresh pool — page is on disk but not in memory
    BufferPool pool{std::move(manager), numFrames};
    auto result = pool.fetchPage(pageId);
    REQUIRE(result.has_value());

    auto readData = result->page->read(0, writeData.size());
    REQUIRE(readData.has_value());
    auto span = *readData;
    REQUIRE(std::ranges::equal(span, writeData));
}