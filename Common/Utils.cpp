#include "Utils.hpp"

std::pair<std::wstring, std::wstring> StrUtils::split(const std::wstring str, char delimiter)
{
	size_t pos = str.find(delimiter);
	std::wstring key = str.substr(0, pos);
	std::wstring val = str.substr(pos + sizeof(char), str.size());

	return std::make_pair(key, val);
}
