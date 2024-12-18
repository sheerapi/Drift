#pragma once

#ifndef DT_NO_DESKTOP
#	include "EventLoop.h"
#	include "GLFW/glfw3.h"
#	include "core/Macros.h"

namespace Drift::Events
{
	class dt_api DesktopEventLoop : public EventLoop
	{
	public:
		void Tick() override;
		void Start() override;
		void HandleView(const std::shared_ptr<View>& view) override;
		~DesktopEventLoop() override;
	};

	namespace Internals
	{
		void glfwCursorEnterCallback(GLFWwindow* window, int entered);
		void glfwMouseButtonCallback(GLFWwindow* window, int button, int action,
									 int mods);
		void glfwKeyCallback(GLFWwindow* window, int key, int scancode, int action,
									 int mods);
		void glfwCursorMoveCallback(GLFWwindow* window, double xpos, double ypos);
		void glfwCursorScrollCallback(GLFWwindow* window, double xoff, double yoff);
	}
}
#endif