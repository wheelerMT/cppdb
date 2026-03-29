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

std::size_t DiskManager::pageCount() const {
    return pageCount_;
}

DiskManager::DiskManager(std::fstream file, std::size_t pageCount)
    : file_(std::move(file)),
      pageCount_(pageCount) {}