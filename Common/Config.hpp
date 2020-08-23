#pragma once
#include "File.hpp"

#include <map>

class Config
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
	void parse();

	File m_source;
	std::map<std::wstring, std::wstring> m_params;
};

