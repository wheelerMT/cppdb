#pragma once
#include "cppdb/page.h"

#include <expected>
#include <filesystem>
#include <fstream>
#include <string>

class DiskManager {
  public:
    static std::expected<DiskManager, std::string> open(const std::filesystem::path& path);
    [[nodiscard]] std::uint32_t pageCount() const;
    [[nodiscard]] std::expected<std::uint32_t, std::string> allocatePage();
    std::expected<void, std::string> writePage(std::uint32_t pageId, const Page& page);
    std::expected<void, std::string> readPage(std::uint32_t pageId, Page& page);

  private:
    explicit DiskManager(std::fstream file, std::uint32_t pageCount);
    std::fstream file_;
    std::uint32_t pageCount_{};
};
