#pragma once
#include "Config.hpp"
#include "RegistryKey.hpp"

class RegistryConfig final : public Config
{
public:
	explicit RegistryConfig(const std::wstring& path);
	~RegistryConfig() = default;

	[[nodiscard]] std::wstring get(const std::wstring& key) const override;

	RegistryConfig(const RegistryConfig&) = delete;
	RegistryConfig(RegistryConfig&&) = delete;
	RegistryConfig operator=(const RegistryConfig&) = delete;
	RegistryConfig operator=(RegistryConfig&&) = delete;

private:
	static RegistryKey open(const std::wstring& path);

	RegistryKey m_registry_key;
};

