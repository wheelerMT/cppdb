#include "cppdb/disk_manager.h"

#include "cppdb/page.h"

DiskManager::DiskManager(const std::filesystem::path& path) {
    if (std::filesystem::exists(path)) {
        file_.open(path, std::ios::binary | std::ios::in | std::ios::out);
    } else {
        file_.open(path, std::ios::binary | std::ios::in | std::ios::out | std::ios::trunc);
    }

    pageCount_ = std::filesystem::file_size(path) / Page::PAGE_SIZE;
}