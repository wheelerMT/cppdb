#pragma once
#include <filesystem>
#include <fstream>

class DiskManager {
  public:
    explicit DiskManager(const std::filesystem::path& path);

  private:
    std::fstream file_;
    std::size_t pageCount_{};
};
