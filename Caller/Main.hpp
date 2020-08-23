#pragma once
#include "Config.hpp"

enum FileArgs
{
	EXE_PATH,
	CONFIG_PATH,
	ARGS_COUNT
};

int wmain(const uint32_t argc, wchar_t* argv[]);
static void run(const Config& config);