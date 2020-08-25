#include "File.hpp"
#include "Utils.hpp"

#include <exception>

enum FileArgs
{
	EXE_PATH,
	FILE_PATH,
	ARGS_COUNT
};

int wmain(const uint32_t argc, wchar_t* argv[])
{
	try {
		constexpr uint32_t BUFFER_SIZE = 4;

		if (argc < ARGS_COUNT) {
			throw std::exception("Path is missing! usage: program.exe <path>");
		}
		// CR: what did we say about splitting the main
		const File file(argv[FILE_PATH]);
		const Buffer result = file.read(BUFFER_SIZE);

		PRINT_LOG(L"Result 0x%x\n", BufferUtils::buffer_to_int(result));

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