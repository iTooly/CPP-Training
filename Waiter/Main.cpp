#include "Waiter.hpp"
#include "RegistryConfig.hpp"
#include "FileConfig.hpp"
#include "Utils.hpp"

#include <exception>

enum WaiterArguments
{
	EXE_PATH,
	CONFIG_TYPE,
	CONFIG_PATH,
	ARGS_COUNT
};

int wmain(const uint32_t argc, wchar_t* argv[])
{
	try {
		if (argc < ARGS_COUNT) {
			throw std::exception("Config file is missing! usage: program.exe <-f | -r> <config_path>");
		}

		const std::wstring reg_flag = L"-r";
		const std::wstring file_flag = L"-f";
		constexpr uint32_t STRINGS_EQUAL = 0;

		if (reg_flag.compare(argv[CONFIG_TYPE]) == STRINGS_EQUAL) {
			const RegistryConfig config(argv[CONFIG_PATH]);
			Waiter::run(config);
		}
		else if (file_flag.compare(argv[CONFIG_TYPE]) == STRINGS_EQUAL) {
			const FileConfig config(argv[CONFIG_PATH]);
			Waiter::run(config);
		}
		else {
			throw std::exception("Config file type is not defined! usage: program.exe <-f | -r> <config_path>");
		}

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