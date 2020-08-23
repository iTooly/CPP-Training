#pragma once
#include "Types.hpp"

#include <Windows.h>
#include <filesystem>

constexpr size_t EOF_LENGTH = 3;

class File final
{
public:
	explicit File(const std::filesystem::path& path);
	~File();

	Buffer read(uint32_t length) const;

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
	constexpr size_t FIRST_INDEX = 0;
	constexpr char NEWLINE = '\n';

	inline uint8_t read_byte(const File& file)
	{
		return file.read(sizeof(uint8_t))[FIRST_INDEX];
	}

	Buffer read_line(const File& file);
}