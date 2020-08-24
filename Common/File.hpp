#pragma once
#include "Types.hpp"

#include <Windows.h>
#include <filesystem>

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
	constexpr BOOL EOF_NOT_SET = FALSE;
	inline uint8_t read_byte(const File& file, BOOL& eof_flag_out);
	Buffer read_line(const File& file, BOOL& eof_flag_out);
}