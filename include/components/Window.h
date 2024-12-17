#pragma once

#ifndef DT_NO_DESKTOP
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
		void Render() override;
		void Update() override;
		auto GetBoundingBox() -> BoundingBox override;

		void DependsOn(const std::shared_ptr<Window>& parent);
		auto HasDependencies() -> bool;
		auto GetInternalWindowHandle() -> void*;

	private:
		std::string _title;
		Window* _depends{nullptr};
		int _width;
		int _height;
		GLFWwindow* _window{nullptr};
	};
}
#endif