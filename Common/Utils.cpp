#include "Utils.hpp"

std::pair<std::wstring, std::wstring> StrUtils::split(const std::wstring& str, char delimiter)
{
	const size_t pos = str.find(delimiter);
	std::wstring key = str.substr(0, pos);
	std::wstring val = str.substr(pos + sizeof(char), str.size());

	return { key, val }; // CR: use make_pair
}

uint32_t BufferUtils::buffer_to_int(const Buffer& buffer)
{
	return *reinterpret_cast<const uint32_t*>(buffer.data());
}

std::wstring BufferUtils::buffer_to_wstring(const Buffer& buffer)
{
	return std::wstring(buffer.begin(), buffer.end());
}
