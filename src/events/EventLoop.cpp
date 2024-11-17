#include "events/EventLoop.h"
#include "utils/Demangle.h"

namespace Drift
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
}