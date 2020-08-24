#include "Caller.hpp"
#include "Event.hpp"
#include "ConfigKeys.hpp"

void Caller::run(const Config& config)
{
	const Event event(config.get(ConfigKeys::EVENT_NAME_KEY));
	event.set();
}