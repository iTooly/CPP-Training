#include "Main.hpp"
#include "Config.hpp"
#include "Program.hpp"
#include "Utils.hpp"

#include <exception>

int wmain(const uint32_t argc, wchar_t* argv[])
{
	try {
		if (argc < ARGS_COUNT) {
			throw std::exception("Config file is missing! usage: program.exe <config_path>");
		}

		const Config config(argv[CONFIG_PATH]);
		Program::run(config);

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