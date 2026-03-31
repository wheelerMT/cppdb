#pragma once
#include "cppdb/disk_manager.h"

#include <vector>

struct Frame {
    Page page{0};
    std::uint32_t pageId{0};
    int pinCount{0};
    bool isOccupied{false};
};

class BufferPool {
  public:
    BufferPool(DiskManager&& manager, std::size_t numFrames);
    [[nodiscard]] std::size_t numFrames() const;

  private:
    DiskManager manager_;
    std::vector<Frame> frames_;
};