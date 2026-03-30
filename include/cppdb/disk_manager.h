#pragma once
#include <cstddef>
#include <expected>
#include <filesystem>
#include <fstream>

class DiskManager {
  public:
    static std::expected<DiskManager, std::string> open(const std::filesystem::path& path);
    [[nodiscard]] std::size_t pageCount() const;
    [[nodiscard]] std::expected<std::size_t, std::string> allocatePage();

  private:
    explicit DiskManager(std::fstream file, std::size_t pageCount);
    std::fstream file_;
    std::uint32_t pageCount_{};
};
