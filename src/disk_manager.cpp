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

    return DiskManager(std::move(file), static_cast<std::uint32_t>(pageCount));
}

std::uint32_t DiskManager::pageCount() const {
    return pageCount_;
}

std::expected<std::uint32_t, std::string> DiskManager::allocatePage() {
    const auto pageId = pageCount_;
    const Page page{pageId};

    if (const auto result = writePage(pageId, page); !result.has_value()) {
        return std::unexpected("failed to allocate page");
    }

    pageCount_++;
    return pageId;
}

std::expected<void, std::string> DiskManager::writePage(const std::uint32_t pageId,
                                                        const Page& page) {
    if (pageId > pageCount_) {
        return std::unexpected("page ID out of range");
    }

    file_.seekp(static_cast<std::streamoff>(pageId) * static_cast<std::streamoff>(Page::PAGE_SIZE));
    file_.write(reinterpret_cast<const char*>(page.rawData().data()), Page::size());

    if (file_.fail()) {
        return std::unexpected("failed to write page");
    }
    file_.flush();

    return {};
}

std::expected<void, std::string> DiskManager::readPage(const std::uint32_t pageId, Page& page) {
    if (pageId >= pageCount_) {
        return std::unexpected("page ID out of range");
    }

    file_.seekg(static_cast<std::streamoff>(pageId) * static_cast<std::streamoff>(Page::PAGE_SIZE));
    std::array<std::byte, Page::PAGE_SIZE> buffer{};
    file_.read(reinterpret_cast<char*>(buffer.data()), Page::PAGE_SIZE);

    if (file_.fail()) {
        return std::unexpected("failed to read page");
    }

    if (const auto result = page.loadData(buffer); !result.has_value()) {
        return std::unexpected("failed to load data into page");
    }
    return {};
}

DiskManager::DiskManager(std::fstream file, std::uint32_t pageCount)
    : file_(std::move(file)),
      pageCount_(pageCount) {}