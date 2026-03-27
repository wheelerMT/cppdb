#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <span>

class Page {
  public:
    static constexpr std::size_t PAGE_SIZE = 4096;
    explicit Page(std::uint32_t pageId);
    [[nodiscard]] static constexpr std::size_t size() { return PAGE_SIZE; }
    [[nodiscard]] bool isDirty() const;
    void write(std::size_t offset, std::span<const std::byte> data);
    [[nodiscard]] std::span<const std::byte> read(std::size_t offset, std::size_t length);

  private:
    std::uint32_t pageId_;
    bool isDirty_{false};
    std::array<std::byte, PAGE_SIZE> data_{};
};
