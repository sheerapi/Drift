#pragma once
#include "../core/View.h"
#include "GLFW/glfw3.h"
#include "core/Macros.h"

namespace Drift
{
	class dt_api Window : public View
	{
	public:
		Window(const std::string& title, int width = 800, int height = 600);
		~Window() override;
		void Present() override;
		void Close() override;

	private:
		std::string _title;
		int _width;
		int _height;
		GLFWwindow* _window{nullptr};
	};
}