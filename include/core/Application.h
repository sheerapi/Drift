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
		auto Present() -> int;

	private:
		ApplicationID _id;
		EnvironmentInfo _env;
	};
}