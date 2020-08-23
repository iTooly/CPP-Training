#pragma once
#include "File.hpp"

#include <map>

constexpr const wchar_t* EVENT_NAME_KEY = L"event_name";

class Config final
{
public:
	explicit Config(const std::filesystem::path& path);
	~Config();

	std::wstring get(const std::wstring& key) const;

	Config(const Config&) = delete;
	Config(Config&&) = delete;
	Config operator=(const Config&) = delete;
	Config operator=(Config&&) = delete;

private:
	static std::map<std::wstring, std::wstring> parse(const File& file);

	File m_source;
	std::map<std::wstring, std::wstring> m_params;
};

