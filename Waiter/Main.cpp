#include "Config.hpp"
#include "Waiter.hpp"
#include "Utils.hpp"

#include <exception>

enum WaiterArguments
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

		const Config config(argv[CONFIG_PATH]);
		Waiter::run(config);

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