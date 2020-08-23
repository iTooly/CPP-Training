#pragma once
#include "Types.hpp"

#include <Windows.h>
#include <string>

class Event final
{
public:
	explicit Event(const std::wstring& name);
	~Event();

	void set() const;
	void listen() const;

	Event(const Event&) = delete;
	Event(Event&&) = delete;
	Event operator=(const Event&) = delete;
	Event operator=(Event&&) = delete;

private:
	static HANDLE open(const std::wstring& path);

	HANDLE m_handle;
};

