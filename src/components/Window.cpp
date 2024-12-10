#include "components/Window.h"
#include "GLFW/glfw3.h"
#include "core/Application.h"
#include "core/Logger.h"
#include "events/DesktopEventLoop.h"
#include "utils/PerformanceTimer.h"

namespace Drift
{
	Window::Window(const std::string& title, int width, int height)
	{
		if (!Application::main->HasEventLoop())
		{
			Application::main->AttachEventLoop<Events::DesktopEventLoop>();
		}

		_title = title;
		_width = width;
		_height = height;
	}

    void Window::Present()
    {
        dt_stopwatch();
        
		_window = glfwCreateWindow(_width, _height, _title.c_str(), nullptr, nullptr);

		if (_window == nullptr)
		{
			dt_coreError("Failed to create Glfw window!");
			return;
		}
	}

    void Window::Close()
    {
        Running = false;
    }

    Window::~Window()
    {
        glfwDestroyWindow(_window);
    }
}