#pragma once
#include "Types.hpp"

#include <Windows.h>
#include <string>
#include <map>


class RegistryKey final
{
public:
	explicit RegistryKey(const RegistryKey& key, const std::wstring& sub_key);
	explicit RegistryKey(const std::wstring& root_key);
	~RegistryKey();

	[[nodiscard]] RegistryKey subkey(const std::wstring& name) const;
	[[nodiscard]] bool is_predefined_key() const;
	[[nodiscard]] std::wstring get(const std::wstring& value) const;

	RegistryKey(const RegistryKey&) = delete;
	RegistryKey(RegistryKey&&) = delete;
	RegistryKey operator=(const RegistryKey&) = delete;
	RegistryKey operator=(RegistryKey&&) = delete;

private:
	explicit RegistryKey(HKEY key);

	[[nodiscard]] HKEY open(const std::wstring& name) const;
	
	[[nodiscard]] static bool is_predefined_key(HKEY key);
	[[nodiscard]] static bool is_predefined_key(const std::wstring& name);

	inline static std::map<std::wstring, HKEY> m_predefined_keys = {
		{L"HKLM", HKEY_LOCAL_MACHINE},
		{L"HCU", HKEY_CURRENT_USER},
		{L"HU", HKEY_USERS},
		{L"HCR", HKEY_CLASSES_ROOT}
	};
	
	HKEY m_key;
};

