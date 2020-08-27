#pragma once
#include "File.hpp"

class Config
{
public:
	Config() = default;
	virtual ~Config() = default;

	[[nodiscard]] virtual std::wstring get(const std::wstring& key) const = 0;

	Config(const Config&) = delete;
	Config(Config&&) = delete;
};

