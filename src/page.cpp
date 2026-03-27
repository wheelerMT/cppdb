#include "cppdb/page.h"

Page::Page(const std::uint32_t pageId) : pageId_(pageId) {}

bool Page::isDirty() const {
    return isDirty_;
}
