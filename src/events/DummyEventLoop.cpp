#include "events/DummyEventLoop.h"
#include <unistd.h>

namespace Drift::Events
{
	void DummyEventLoop::Start()
	{
		for (auto& view : Views)
		{
			view->Present();
		}
	}

	void DummyEventLoop::Tick()
	{
		
	}

	auto DummyEventLoop::IsRunning() -> bool
	{
		return Running;
	}
}