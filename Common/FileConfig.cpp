#include "FileConfig.hpp"

#include "Utils.hpp"

FileConfig::FileConfig(const std::filesystem::path& path)
	: m_params(parse(path))
{
}

std::wstring FileConfig::get(const std::wstring& key) const
{
	return m_params.at(key);
}

std::map<std::wstring, std::wstring> FileConfig::parse(const std::filesystem::path& path)
{
	const File file(path);
	const Buffer buffer = FileUtils::read_all(file);
	constexpr char NEWLINE = '\n';

	const std::vector<std::wstring> lines = StrUtils::split(BufferUtils::buffer_to_wstring(buffer), NEWLINE);
	std::map<std::wstring, std::wstring> params;

	for (const std::wstring& line : lines) {
		constexpr char DELIMITER = '=';
		std::vector<std::wstring> items = StrUtils::split(line, DELIMITER);
		params.insert(std::make_pair(items[0], items[1]));
	}

	return params;
}
