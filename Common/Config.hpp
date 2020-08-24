#pragma once
#include "File.hpp"

#include <map>

class Config final
{
public:
	explicit Config(const std::filesystem::path& path);
	~Config() = default;
	
	std::wstring get(const std::wstring& key) const;

	Config(const Config&) = delete;
	Config(Config&&) = delete;
	Config operator=(const Config&) = delete;
	Config operator=(Config&&) = delete;

private:
	static std::map<std::wstring, std::wstring> parse(const std::filesystem::path& path);

	std::map<std::wstring, std::wstring> m_params;
};

