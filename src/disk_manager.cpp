#include "cppdb/disk_manager.h"

#include "cppdb/page.h"

std::expected<DiskManager, std::string> DiskManager::open(const std::filesystem::path& path) {
    std::fstream file;
    if (std::filesystem::exists(path)) {
        file.open(path, std::ios::binary | std::ios::in | std::ios::out);
    } else {
        file.open(path, std::ios::binary | std::ios::in | std::ios::out | std::ios::trunc);
    }
    if (!file.is_open()) {
        return std::unexpected(std::string{"Unable to open file"});
    }

    const auto pageCount = std::filesystem::file_size(path) / Page::PAGE_SIZE;

    return DiskManager(std::move(file), pageCount);
}

std::uint32_t DiskManager::pageCount() const {
    return pageCount_;
}

std::expected<std::uint32_t, std::string> DiskManager::allocatePage() {
    constexpr std::array<std::byte, Page::PAGE_SIZE> data{};
    const auto pageId = pageCount_;

    // Seek to the write position
    file_.seekp(static_cast<std::streamoff>(pageId) * static_cast<std::streamoff>(Page::PAGE_SIZE));

    // Write to the file
    file_.write(reinterpret_cast<const char*>(data.data()), Page::PAGE_SIZE);

    // Check for write error
    if (file_.fail()) {
        return std::unexpected("failed to write page");
    }
    file_.flush();
    
    pageCount_++;
    return pageId;
}

DiskManager::DiskManager(std::fstream file, std::uint32_t pageCount)
    : file_(std::move(file)),
      pageCount_(pageCount) {}