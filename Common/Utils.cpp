#include "Utils.hpp"

std::vector<Buffer> FileUtils::read_lines(const File& file)
{
	std::vector<Buffer> result;
	uint8_t byte = 0;
	Buffer buffer;

	while (byte != EOF) {
		try {
			byte = file.read();
		}
		catch (const std::exception& e) {
			if (std::strncmp(e.what(), "EOF", 3) == 0) {
				result.push_back(buffer);
				break;
			}

			throw e;
		}

		if (byte == '\n') {
			result.push_back(buffer);

			buffer = Buffer();
			continue;
		}

		buffer.push_back(byte);
	}

	return result;
}

std::pair<std::wstring, std::wstring> StrUtils::split(const std::wstring str, std::wstring delimiter)
{
	size_t pos = str.find(L"=");
	std::wstring key = str.substr(0, pos);
	std::wstring val = str.substr(pos + delimiter.size(), str.size());

	return std::make_pair(key, val);
}
