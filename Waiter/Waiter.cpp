#include "Waiter.hpp"
#include "Event.hpp"
#include "ConfigKeys.hpp"

namespace Waiter
{
	void run(const Config& config)
	{
		const Event event(config.get(ConfigKeys::EVENT_NAME_KEY));
		event.wait();
	}
}