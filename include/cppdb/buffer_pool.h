#pragma once
#include "cppdb/disk_manager.h"
#include "cppdb/page.h"

#include <expected>
#include <string>
#include <unordered_map>
#include <vector>

struct Frame {
    Page page{0};
    std::uint32_t pageId{0};
    int pinCount{0};
    bool isOccupied{false};
};

struct PageHandle {
    Page* page;
    std::uint32_t pageId;
    PageHandle(Page* page, const std::uint32_t pageId) : page(page), pageId(pageId) {}
};

class BufferPool {
  public:
    BufferPool(DiskManager&& manager, std::size_t numFrames);
    [[nodiscard]] std::size_t numFrames() const;
    [[nodiscard]] std::expected<PageHandle, std::string> newPage();
    [[nodiscard]] std::expected<PageHandle, std::string> fetchPage(std::uint32_t pageId);

  private:
    DiskManager manager_;
    std::vector<Frame> frames_;
    std::unordered_map<std::uint32_t, std::size_t> pageTable_;
};