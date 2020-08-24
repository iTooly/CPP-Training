#include "Config.hpp"
#include "Utils.hpp"

Config::Config(const std::filesystem::path& path)
	: m_params(parse(path))
{
}

std::wstring Config::get(const std::wstring& key) const
{
	return m_params.at(key);
}

std::map<std::wstring, std::wstring> Config::parse(const std::filesystem::path& path)
{
	std::map<std::wstring, std::wstring> params;
	const File file(path);
	BOOL eof_flag = FALSE;

	while (eof_flag == FileUtils::EOF_NOT_SET) {
		Buffer buffer = FileUtils::read_line(file, eof_flag);
		constexpr char DELIMITER = '=';
		std::pair<std::wstring, std::wstring> pair = StrUtils::split(BufferUtils::buffer_to_wstring(buffer), DELIMITER);
		params.insert(pair);
	}

	return params;
}
