#include "Event.hpp"
#include "Utils.hpp"

#include <cassert>

Event::Event(const std::wstring& name)
	: m_handle(open(name))
{
}

Event::~Event()
{
	try {
		const BOOL status = CloseHandle(m_handle);
		assert(status != FALSE);
	}
	catch (...) {
		PRINT_LOG(L"Something bad happened while closing the Event.");
	}
}

void Event::set() const
{
	BOOL status = SetEvent(m_handle);

	if (status == FALSE) {
		throw std::exception("An error has occurred while trying to set the Event.");
	}
}

void Event::listen() const
{
	uint32_t status = WaitForSingleObject(m_handle, INFINITE);

	if (status != WAIT_OBJECT_0) {
		throw std::exception("An error has occurred while listening to the Event.");
	}
}

HANDLE Event::open(const std::wstring& name)
{
	constexpr LPSECURITY_ATTRIBUTES DEFAULT_SECURITY_ATTRIBUTES = nullptr;
	constexpr BOOL MANUAL_RESET = TRUE;
	constexpr BOOL INIT_STATE_NONSIGNALED = FALSE;

	HANDLE handle = CreateEventW(DEFAULT_SECURITY_ATTRIBUTES,
								 MANUAL_RESET,
								 INIT_STATE_NONSIGNALED,
								 name.c_str());

	if (handle == NULL) {
		throw std::exception("An error has occurred while trying to open the Event.");
	}

	return handle;
}
