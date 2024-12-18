#ifndef DT_NO_DESKTOP
#	include "events/DesktopEventLoop.h"
#	include "GLFW/glfw3.h"
#	include "components/Window.h"
#	include "utils/PerformanceTimer.h"
#	include "events/InputSystem.h"

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

				glfwSetCursorPosCallback((GLFWwindow*)window->GetInternalWindowHandle(),
										 Internals::glfwCursorMoveCallback);

				glfwSetMouseButtonCallback((GLFWwindow*)window->GetInternalWindowHandle(),
										 Internals::glfwMouseButtonCallback);
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

			if (entered == 0)
			{
				// we have to reset everything since we dont know if we are going
				// to be focused again
				Input::mousePosition = {0, 0};
			}
		}

		void glfwCursorMoveCallback(GLFWwindow* window, double xpos, double ypos)
		{
			Input::TriggerMouseMove({.X = (float)xpos, .Y = (float)ypos});
		}

		void glfwMouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
		{
			Input::TriggerMouseClick((MouseButton)button, action == GLFW_PRESS);
		}

		void glfwCursorScrollCallback(GLFWwindow* window, double xoff, double yoff)
		{
			Input::TriggerMouseScroll({.X = (float)xoff, .Y = (float)yoff});
		}
	}
}
#endif