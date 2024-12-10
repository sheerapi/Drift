#include "events/EventLoop.h"
#include "utils/Demangle.h"

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
		if (Views.empty())
		{
			Running = false;
		}

		for (auto& view : Views)
		{
			if (!view->IsRunning())
			{
				std::erase(Views, view);
			}

			if (view->IsEnabled())
			{
				HandleView(view);
				view->Update();
				view->Render();
			}
		}
	}
}