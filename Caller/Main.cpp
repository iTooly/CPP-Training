#include "Main.hpp"
#include "Event.hpp"
#include "Config.hpp"
#include "Utils.hpp"

#include <exception>

int wmain(const uint32_t argc, wchar_t* argv[])
{
	try {
		if (argc < ARGS_COUNT) {
			throw std::exception("Config file is missing! usage: program.exe <config_path>");
		}

		Config config(argv[CONFIG_PATH]);
		run(config);

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

static void run(const Config& config)
{
	Event event(config.get(EVENT_NAME_KEY));
	event.set();
}