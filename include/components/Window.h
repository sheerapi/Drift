#pragma once
#include "../core/View.h"

namespace Drift
{
    class Window : public View
    {
    public:
		Window(const std::string& title, int width = 800, int height = 600);
	};
}