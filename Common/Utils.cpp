#include "Utils.hpp"

std::vector<std::wstring> StrUtils::split(std::wstring str, char delimiter)
{
	std::vector<std::wstring> list;
	size_t pos = 0;
	
	while (pos != std::wstring::npos)
	{
		pos = str.find(delimiter);
		list.push_back(str.substr(0, pos));
		
		str = str.substr(pos + sizeof(char), str.size());
	}
	
	return list;
}

uint32_t BufferUtils::buffer_to_int(const Buffer& buffer)
{
	return *reinterpret_cast<const uint32_t*>(buffer.data());
}

std::wstring BufferUtils::buffer_to_wstring(const Buffer& buffer)
{
	return std::wstring(buffer.begin(), buffer.end());
}
