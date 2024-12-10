#include "events/DesktopEventLoop.h"
#include "GLFW/glfw3.h"

namespace Drift::Events
{
    void DesktopEventLoop::Start()
    {
		for (auto& view : Views)
		{
			view->Present();
		}
	}

    void DesktopEventLoop::Tick()
    {
        glfwPollEvents();
    }

	void DesktopEventLoop::HandleView(const std::shared_ptr<View>& view)
    {

    }
}