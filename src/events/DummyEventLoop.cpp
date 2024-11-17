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
		if (Views.empty())
		{
			_running = false;
		}
		
		for (auto& view : Views)
		{
			if (!view->IsRunning())
			{
				std::erase(Views, view);
			}

			if (view->IsEnabled())
			{
				view->Update();
				view->Render();
			}
		}
	}

	auto DummyEventLoop::IsRunning() -> bool
	{
		return _running;
	}
}