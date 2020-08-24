#include "Program.hpp"
#include "Event.hpp"
#include "ConfigKeys.hpp"

void Program::run(const Config& config)
{
	const Event event(config.get(EVENT_NAME_KEY));
	event.set();
}