#include "events/DesktopEventLoop.h"
#include "GLFW/glfw3.h"
#include "utils/PerformanceTimer.h"

void driftHandleGlfwError(int err, const char* msg)
{
    dt_coreError("An error ocurred within Glfw: {} ({})", msg, err);
}

namespace Drift::Events
{
    void DesktopEventLoop::Start()
    {
        dt_stopwatch();

        glfwSetErrorCallback(&driftHandleGlfwError);

		glfwInitHint(GLFW_WAYLAND_LIBDECOR, GLFW_WAYLAND_DISABLE_LIBDECOR);

		if (glfwInit() == 0)
        {
            dt_coreError("Failed to initialize Glfw!");
            return;
        }

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

    DesktopEventLoop::~DesktopEventLoop()
    {
        glfwTerminate();
    }
}