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
	uint64_t size() const; // CR: no_discard

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

	// CR: remove this
	/*
	 * DEPRECATED
	 */
	//uint8_t read_byte(const File& file, bool& eof_flag_out);
	//Buffer read_line(const File& file, bool& eof_flag_out);
}