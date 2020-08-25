#pragma once
#include "Types.hpp"

#include <Windows.h>
#include <filesystem>

class File final
{
public:
	explicit File(const std::filesystem::path& path);
	~File();

	[[nodiscard]] Buffer read(uint32_t length) const;
	[[nodiscard]] uint64_t size() const; // CR: no_discard

	File(const File&) = delete;
	File(File&&) = delete;
	File operator=(const File&) = delete;
	File operator=(File&&) = delete;

private:
	static HANDLE open(const std::filesystem::path& path);

	HANDLE m_handle;
};

namespace FileUtils
{
	Buffer read_all(const File& file);
}