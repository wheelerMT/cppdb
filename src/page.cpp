#include "cppdb/page.h"

#include <algorithm>

Page::Page(const std::uint32_t pageId) : pageId_(pageId) {}

bool Page::isDirty() const {
    return isDirty_;
}

void Page::write(const std::size_t offset, std::span<const std::byte> data) {
    isDirty_ = true;
    std::ranges::copy(data, data_.begin() + offset);
}

std::span<const std::byte> Page::read(const std::size_t offset, const std::size_t length) const {
    return std::span{data_.begin() + offset, length};
}
