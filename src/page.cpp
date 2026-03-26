#include "cppdb/page.h"

Page::Page(const std::uint32_t pageId) : pageId_(pageId) {}
std::size_t Page::size() {
    return PAGE_SIZE;
}
