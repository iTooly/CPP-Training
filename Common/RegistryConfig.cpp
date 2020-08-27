#include "RegistryConfig.hpp"
#include "Utils.hpp"

RegistryConfig::RegistryConfig(const std::wstring& path)
	: m_registry_key(open(path))
{
}

std::wstring RegistryConfig::get(const std::wstring& key) const
{
	return m_registry_key.get(key);
}

RegistryKey RegistryConfig::open(const std::wstring& path)
{
	constexpr char DELIMITER = '\\';
	const size_t pos = path.find_first_of(DELIMITER);
	const std::wstring root(path.substr(0, pos));
	const std::wstring key(path.substr(pos + sizeof(DELIMITER)));
	return RegistryKey(root).subkey(key);
}
