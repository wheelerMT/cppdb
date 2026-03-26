#ifndef CPPDB_PAGE_H
#define CPPDB_PAGE_H
#include <cstddef>
#include <cstdint>

class Page {
  public:
    static constexpr std::size_t PAGE_SIZE = 4096;
    explicit Page(std::uint32_t pageId);
    static std::size_t size();

  private:
    std::uint32_t pageId_;
};
#endif // CPPDB_PAGE_H
