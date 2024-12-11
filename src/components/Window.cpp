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

        glfwMakeContextCurrent(_window);

        _context = std::make_shared<Graphics::RendererContext>(_width, _height);
	}

    void Window::Update()
    {
        if (glfwWindowShouldClose(_window) == GLFW_TRUE)
        {
            Close();
        }
    }

    void Window::Render()
    {
        glfwMakeContextCurrent(_window);

		glfwGetFramebufferSize(_window, &_width, &_height);
		_context->RefreshContext(_width, _height);

		_context->Canvas->clear(SK_ColorWHITE);
        _context->GrContext->flushAndSubmit();

        glfwSwapBuffers(_window);
	}

    void Window::Close()
    {
        if (Running)
        {
			Running = false;
			glfwDestroyWindow(_window);
			glfwMakeContextCurrent(nullptr);
			_window = nullptr;
		}
    }

    Window::~Window()
    {
        // this shit duplicate is actually needed for the close to work lmaoo
        // dont ask
        if (!Running)
        {
            return;
        }

        glfwDestroyWindow(_window);
		glfwMakeContextCurrent(nullptr);
		_window = nullptr;
	}
}