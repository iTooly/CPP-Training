#include "Caller.hpp"
#include "Event.hpp"
#include "ConfigKeys.hpp"

// CR: prefer this:
// namespace Caller
// {
// ...
// }
void Caller::run(const Config& config)
{
	const Event event(config.get(ConfigKeys::EVENT_NAME_KEY));
	event.set();
}