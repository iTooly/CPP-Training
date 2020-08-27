#pragma once
#include "File.hpp"
#include "Config.hpp"

#include <map>

class FileConfig final : public Config
{
public:
	explicit FileConfig(const std::filesystem::path& path);
	~FileConfig() override = default;
	
	[[nodiscard]] std::wstring get(const std::wstring& key) const override;

	FileConfig(const FileConfig&) = delete;
	FileConfig(FileConfig&&) = delete;
	FileConfig operator=(const FileConfig&) = delete;
	FileConfig operator=(FileConfig&&) = delete;

private:
	static std::map<std::wstring, std::wstring> parse(const std::filesystem::path& path);

	std::map<std::wstring, std::wstring> m_params;
};

