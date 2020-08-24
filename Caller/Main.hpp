#pragma once
#include "Config.hpp"

enum FileArgs
{
	EXE_PATH,
	CONFIG_PATH,
	ARGS_COUNT
};

namespace Main
{
	void run(const Config& config);
}