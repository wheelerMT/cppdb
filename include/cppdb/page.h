#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <expected>
#include <span>

class Page {
  public:
    static constexpr std::size_t PAGE_SIZE = 4096;
    explicit Page(std::uint32_t pageId);
    [[nodiscard]] static constexpr std::size_t size() { return PAGE_SIZE; }
    [[nodiscard]] bool isDirty() const;
    std::expected<void, std::string> write(std::size_t offset, std::span<const std::byte> data);
    [[nodiscard]] std::expected<std::span<const std::byte>, std::string>
    read(std::size_t offset, std::size_t length) const;

  private:
    std::uint32_t pageId_;
    bool isDirty_{false};
    std::array<std::byte, PAGE_SIZE> data_{};
};
