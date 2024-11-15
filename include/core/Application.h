#pragma once
#include "core/ApplicationInfo.h"
#include <string>

namespace Drift
{
	class Application
	{
	public:
		inline static Application* main{nullptr};

		Application(const std::string& appId);
		void Present();

	private:
		ApplicationID _id;
	};
}