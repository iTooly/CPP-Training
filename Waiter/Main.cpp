#include "Event.hpp"
#include "Config.hpp"
#include "Utils.hpp"

#include <exception>

enum FileArgs
{
	EXE_PATH,
	CONFIG_PATH,
	ARGS_COUNT
};

int wmain(const uint32_t argc, wchar_t* argv[])
{
	try {
		if (argc < ARGS_COUNT) {
			throw std::exception("Config file is missing! usage: program.exe <config_path>");
		}

		constexpr const wchar_t* EVENT_NAME_KEY = L"event_name";

		Config config(argv[CONFIG_PATH]);
		Event event(config.get(EVENT_NAME_KEY));

		event.listen();

		return EXIT_SUCCESS;
	}
	catch (const std::exception& e) {
		PRINT_LOG(L"%hs\n Error Code: %d\n", e.what(), GetLastError());
	}
	catch (...) {
		PRINT_LOG(L"Something very bad happend!\n");
	}

	return EXIT_FAILURE;
}