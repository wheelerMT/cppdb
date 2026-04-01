#include "cppdb/buffer_pool.h"

#include <algorithm>

BufferPool::BufferPool(DiskManager&& manager, size_t numFrames) : manager_(std::move(manager)) {
    frames_.resize(numFrames);
}

std::size_t BufferPool::numFrames() const {
    return frames_.size();
}

std::expected<PageHandle, std::string> BufferPool::newPage() {
    const auto result = manager_.allocatePage();
    if (!result.has_value()) {
        return std::unexpected(result.error());
    }
    const auto pageId = result.value();

    // Find a free frame to add the Page to
    const auto iter =
        std::ranges::find_if(frames_, [](const Frame& frame) { return !frame.isOccupied; });
    if (iter == frames_.end()) {
        return std::unexpected("buffer pool is full");
    }

    // Add page to table
    const auto frameIndex = static_cast<std::size_t>(std::distance(frames_.begin(), iter));
    pageTable_[pageId] = frameIndex;

    // Update frame and return result
    iter->isOccupied = true;
    iter->page = Page{pageId};
    iter->pageId = pageId;
    iter->pinCount = 1;

    return PageHandle{&iter->page, pageId};
}