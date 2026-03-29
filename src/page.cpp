#include "cppdb/page.h"

#include <algorithm>

using std::string_literals::operator""s;

Page::Page(const std::uint32_t pageId) : pageId_(pageId) {}

bool Page::isDirty() const {
    return isDirty_;
}

std::expected<void, std::string> Page::write(const std::size_t offset,
                                             std::span<const std::byte> data) {
    if (offset + data.size() > PAGE_SIZE) {
        return std::unexpected(
            std::string("Write operation would exceed the bounds of page memory"));
    }

    isDirty_ = true;
    std::ranges::copy(data, data_.begin() + offset);
    return {};
}

std::expected<std::span<const std::byte>, std::string> Page::read(const std::size_t offset,
                                                                  const std::size_t length) const {
    if (offset + length > PAGE_SIZE) {
        return std::unexpected(
            std::string("Read operation would exceed the bounds of page memory"));
    }

    return std::span{data_.begin() + offset, length};
}

std::span<const std::byte> Page::rawData() const {
    return std::span{data_.begin(), data_.end()};
}

std::expected<void, std::string> Page::loadData(std::span<const std::byte> bytes) {
    if (bytes.size() != PAGE_SIZE) {
        return std::unexpected("Bytes do not match page size of 4096"s);
    }

    std::ranges::copy(bytes, data_.begin());
    isDirty_ = false;

    return {};
}
