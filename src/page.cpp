#include "cppdb/page.h"

Page::Page(const std::uint32_t pageId) : pageId_(pageId) {}

bool Page::isDirty() const {
    return isDirty_;
}
void Page::write(std::size_t offset, std::span<const std::byte> data) {
    isDirty_ = true;
}
