#ifndef DT_NO_DESKTOP
#	include "events/DesktopEventLoop.h"
#	include "GLFW/glfw3.h"
#	include "components/Window.h"
#	include "utils/PerformanceTimer.h"
#	include "events/InputSystem.h"
#	include "core/Application.h"

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

			if (reinterpret_cast<Window*>(view.get()) != nullptr)
			{
				auto* window = reinterpret_cast<Window*>(view.get());

				glfwSetCursorEnterCallback((GLFWwindow*)window->GetInternalWindowHandle(),
										   Internals::glfwCursorEnterCallback);
			}
		}

		Update();
		ForceLayoutRefresh();
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

	namespace Internals
	{
		void glfwCursorEnterCallback(GLFWwindow* window, int entered)
		{
			auto* dt_window = (Window*)glfwGetWindowUserPointer(window);
			dt_window->EmitSignal(entered == GLFW_TRUE ? "cursor.entered"
													   : "cursor.exit");

            Input::currentView = entered == 1 ? dt_window : nullptr;
		}
	}
}
#endif