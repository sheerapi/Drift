#ifndef DT_NO_DESKTOP
#	include "components/Window.h"
#	include "GLFW/glfw3.h"
#	include "core/Activity.h"
#	include "core/Application.h"
#	include "core/Logger.h"
#	include "core/SkColor.h"
#	include "events/DesktopEventLoop.h"
#	include "graphics/RendererContext.h"
#	include "utils/PerformanceTimer.h"

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

		glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
		glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);
		glfwWindowHint(GLFW_SRGB_CAPABLE, GLFW_TRUE);
		glfwWindowHint(GLFW_SCALE_TO_MONITOR, GLFW_TRUE);
		glfwWindowHintString(GLFW_X11_CLASS_NAME,
							 Application::GetApplicationID().GetCompoundID().c_str());

		_window = glfwCreateWindow(_width, _height, _title.c_str(), nullptr, nullptr);

		if (_window == nullptr)
		{
			dt_coreError("Failed to create Glfw window!");
			return;
		}

		glfwSetWindowUserPointer(_window, this);

		glfwMakeContextCurrent(_window);

		glfwGetFramebufferSize(_window, &_width, &_height);
		glfwSwapInterval(1);

		RendererContext = std::make_shared<Graphics::RendererContext>(_width, _height);
	}

	void Window::Update()
	{
		if (_depends != nullptr && !_depends->IsRunning())
		{
			Close();
			return;
		}

		if (glfwWindowShouldClose(_window) == GLFW_TRUE)
		{
			Close();
			return;
		}

		glfwGetFramebufferSize(_window, &_width, &_height);

		for (auto& activity : Activities)
		{
			activity->SetContainingView(this);
			activity->Update();
		}
		
		DestroyedActivities.erase(
			std::remove_if(
				DestroyedActivities.begin(), DestroyedActivities.end(), [](auto& activity)
				{ return activity->GetStatus() == Activity::Status::Destroyed; }),
			DestroyedActivities.end());
	}

	void Window::Render()
	{
		Graphics::RendererContext::main = RendererContext;

		glfwMakeContextCurrent(_window);

		RendererContext->RefreshContext(_width, _height);

		RendererContext->Canvas->clear(SK_ColorTRANSPARENT);

		for (auto& activity : Activities)
		{
			activity->Render();
		}

		for (auto& activity : DestroyedActivities)
		{
			activity->Render();
		}

		RendererContext->GrContext->flushAndSubmit();

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

	void Window::DependsOn(const std::shared_ptr<Window>& parent)
	{
		_depends = parent.get();
	}

	auto Window::HasDependencies() -> bool
	{
		return _depends == nullptr;
	}

	auto Window::GetBoundingBox() -> BoundingBox
	{
		return {(float)_width, (float)_height, 0, 0};
	}

	auto Window::GetInternalWindowHandle() -> void*
	{
		return _window;
	}
}
#endif