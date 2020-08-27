#include "RegistryKey.hpp"
#include "Utils.hpp"

#include <Windows.h>
#include <cassert>

RegistryKey::RegistryKey(const HKEY key)
	: m_key(key)
{
}

RegistryKey::RegistryKey(const RegistryKey& key, const std::wstring& sub_key)
	: m_key(key.open(sub_key))
{
}

RegistryKey::RegistryKey(const std::wstring& root_key)
	: RegistryKey(m_predefined_keys.find(root_key)->second)
{
}

RegistryKey::~RegistryKey()
{
	try {
		if (is_predefined_key() == FALSE) {
			const LSTATUS status = RegCloseKey(m_key);
			assert(status == ERROR_SUCCESS);
		}
	}
	catch (...) {
		PRINT_LOG(L"Something bad happened while closing the RegistryKey.");
	}
}

RegistryKey RegistryKey::subkey(const std::wstring& name) const
{
	return RegistryKey(open(name));
}

bool RegistryKey::is_predefined_key() const
{
	return is_predefined_key(m_key);
}

std::wstring RegistryKey::get(const std::wstring& value) const
{
	constexpr uint32_t MAX_BUFFER = 1024;
	constexpr LPDWORD RESERVED = nullptr;
	Buffer result(1024, NULL);
	DWORD size = MAX_BUFFER;
	DWORD type = NULL;
	const LSTATUS status = RegQueryValueExW(m_key,
											value.c_str(),
											RESERVED,
											&type,
											result.data(),
											&size);

	if (status != ERROR_SUCCESS) {
		throw std::exception("An error has occurred while trying to read a value");
	}

	if (type != REG_SZ) {
		throw std::exception("An error has occurred while trying to read a value, the value's type is not REG_SZ.");
	}
	
	return std::wstring(reinterpret_cast<wchar_t*>(result.data()));
}

HKEY RegistryKey::open(const std::wstring& name) const
{
	const auto key = m_predefined_keys.find(name);
	if (key != m_predefined_keys.end())
	{
		return key->second;
	}
	
	constexpr DWORD DEFAULT_OPTIONS = NULL;
	HKEY result = nullptr;
	const LSTATUS status = RegOpenKeyExW(m_key,
										 name.c_str(),
										 DEFAULT_OPTIONS,
										 KEY_READ,
										 &result);

	if (status != ERROR_SUCCESS) {
		throw std::exception("An error has occurred while trying to open the SubKey.");
	}

	return result;
}

bool RegistryKey::is_predefined_key(const HKEY key)
{
	for (auto item = m_predefined_keys.begin(); item != m_predefined_keys.end(); ++item)
	{
		if (item->second == key) {
			return true;
		}
	}
		
	return false;
}

bool RegistryKey::is_predefined_key(const std::wstring& name)
{
	return m_predefined_keys.find(name) != m_predefined_keys.end();
}
