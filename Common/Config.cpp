#include "Config.hpp"
#include "Utils.hpp"

Config::Config(const std::filesystem::path& path)
	: m_source(path),
	m_params(parse(m_source))
{
}

Config::~Config()
{
}

std::wstring Config::get(const std::wstring& key) const
{
	return m_params.at(key);
}

std::map<std::wstring, std::wstring> Config::parse(const File& file)
{
	std::map<std::wstring, std::wstring> params;

	try {
		constexpr char DELIMITER = '=';

		while (TRUE) {
			Buffer buffer = FileUtils::read_line(file);
			std::pair<std::wstring, std::wstring> pair = StrUtils::split(BufferUtils::buffer_to_wstring(buffer), DELIMITER);
			params.insert(pair);
		}
	}
	catch (const std::exception& e) {
		if (std::strncmp(e.what(), "EOF", EOF_LENGTH) != NULL) {
			throw e;
		}
	}

	return params;
}
