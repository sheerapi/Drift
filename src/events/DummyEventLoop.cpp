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
		for (auto& view : Views)
		{
			if (view->IsEnabled())
			{
				view->Update();
				view->Render();
			}
		}
	}

	auto DummyEventLoop::IsRunning() -> bool
	{
		return true;
	}
}