#pragma once
#include "Types.hpp"
#include "File.hpp"

namespace LogUtils
{
#define PRINT_LOG(format, ...)				\
	do {									\
		try {								\
			wprintf(format, ##__VA_ARGS__);	\
		}									\
		catch(...)							\
		{									\
		}									\
	}										\
	while(false)
}

namespace BufferUtils
{
	inline uint32_t buffer_to_int(const Buffer& buffer)
	{
		return *reinterpret_cast<const uint32_t*>(buffer.data());
	}

	inline std::wstring buffer_to_wstring(const Buffer& buffer)
	{
		return std::wstring(buffer.begin(), buffer.end());
	}
}

namespace FileUtils
{
	std::vector<Buffer> read_lines(const File& file);
}

namespace StrUtils
{
	std::pair<std::wstring, std::wstring> split(const std::wstring str, std::wstring delimiter);
}