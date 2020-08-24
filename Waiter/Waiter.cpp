#include "Waiter.hpp"
#include "Event.hpp"
#include "ConfigKeys.hpp"

void Waiter::run(const Config& config)
{
	const Event event(config.get(ConfigKeys::EVENT_NAME_KEY));
	event.wait();
}