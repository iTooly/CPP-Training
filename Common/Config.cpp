#include "Config.hpp"
#include "Utils.hpp"

Config::Config(const std::filesystem::path& path)
	: m_source(path),
	m_params()
{
	parse();
}

Config::~Config()
{
}

std::wstring Config::get(const std::wstring& key) const
{
	return m_params.at(key);
}

void Config::parse()
{
	constexpr const wchar_t* DELIMITER = L"=";

	std::vector<Buffer> list = FileUtils::read_lines(m_source);
	for (size_t i = 0; i < list.size(); i++) {
		std::pair<std::wstring, std::wstring> pair = StrUtils::split(BufferUtils::buffer_to_wstring(list[i]), DELIMITER);
		m_params.insert(pair);
	}
}
