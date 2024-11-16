#include "events/DummyEventLoop.h"
#include <unistd.h>

namespace Drift::Events
{
	void DummyEventLoop::Tick()
	{
		sleep(1);
	}

	auto DummyEventLoop::IsRunning() -> bool
	{
		return true;
	}
}