#pragma once
#include <filesystem>
#include <fstream>

class DiskManager {
  public:
    explicit DiskManager(const std::filesystem::path& path);
    [[nodiscard]] std::size_t pageCount() const;

  private:
    std::fstream file_;
    std::size_t pageCount_{};
};
