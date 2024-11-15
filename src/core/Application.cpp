#include "core/Application.h"
#include "core/ApplicationInfo.h"
#include "core/Logger.h"

namespace Drift
{
	Application::Application(const std::string& appId)
	{
		Logger::Init();

		if (main != nullptr)
		{
			dt_coreFatal("Another application instance is running!");
		}

		main = this;

		_id = ApplicationID(appId);
		_env = EnvironmentInfo();

		dt_coreInfo("Initialized \"{}\"", _id.GetCompoundID());
	}
}