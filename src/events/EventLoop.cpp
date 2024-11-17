#include "events/EventLoop.h"
#include "utils/Demangle.h"

namespace Drift
{
    void EventLoop::PrintViewTree()
    {
        dt_coreDebug("root@{}", getNamespaceFreeName(dt_type(*this)));
        
        for (auto& view : Views)
        {
            view->PrintElementTree();
        }
    }
}