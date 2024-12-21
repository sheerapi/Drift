#include "events/EventLoop.h"
#include "utils/Demangle.h"
#include "utils/Time.h"

namespace Drift::Events
{
	void EventLoop::PrintViewTree()
	{
		// padding bc this is too messy lol
		dt_coreDebug(" ");
		dt_coreDebug("root@{}", getNamespaceFreeName(dt_type(*this)));

		for (auto& view : Views)
		{
			view->PrintElementTree();
		}

		dt_coreDebug(" ");
	}

	void EventLoop::Update()
	{
		Time::Update();
		
		if (Views.empty())
		{
			Running = false;
			return;
		}

		if (Running)
		{
			Tick();
		}

		for (auto& view : Views)
		{
			if (view->IsEnabled())
			{
				HandleView(view);
				view->Update();
				
				if (view->IsRunning())
				{
					// window could have been closed mid update
					view->Render();
				}
			}
		}

		Views.erase(std::remove_if(Views.begin(), Views.end(), [](auto& view)
								   { return view == nullptr || !view->IsRunning(); }),
					Views.end());
	}

	void EventLoop::ForceLayoutRefresh()
	{
		for (auto& view : Views)
		{
			view->ForceLayoutRefresh();
		}
	}
}