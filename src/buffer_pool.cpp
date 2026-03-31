#include "cppdb/buffer_pool.h"

BufferPool::BufferPool(DiskManager&& manager, size_t numFrames) : manager_(std::move(manager)) {
    frames_.resize(numFrames);
}

std::size_t BufferPool::numFrames() const {
    return frames_.size();
}