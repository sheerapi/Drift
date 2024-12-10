#include "core/Application.h"
#include "core/ApplicationInfo.h"
#include "utils/Demangle.h" // IWYU pragma: keep
#include "utils/LibraryManager.h"
#include "utils/PerformanceTimer.h"

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

		dt_stopwatch();

		_id = ApplicationID(appId);
		_env = EnvironmentInfo();

		LibraryManager::Init();

		dt_coreInfo("Initialized \"{}\"", _id.GetCompoundID());
	}

	auto Application::Present() -> int
	{
		if (_eventLoop == nullptr)
		{
			dt_coreError("No event loop attached!");
			return 2;
		}

		if (_presented)
		{
			dt_coreError("Application already presented!");
			return 3;
		}

		_presented = true;

		try
		{
			_eventLoop->Start();

			while (_eventLoop->IsRunning())
			{
				_eventLoop->Update();
			}
		}
		catch (const std::exception& e)
		{
			auto& evloop = *_eventLoop;

			dt_coreFatal("An error ocurred when executing \"{}\": {}", dt_type(evloop),
						 e.what());
			return 4;
		}

		return 0;
	}

	auto Application::HasEventLoop() -> bool
	{
		return _eventLoop != nullptr;
	}

	auto Application::GetEventLoop() -> std::shared_ptr<Events::EventLoop>
	{
		return _eventLoop;
	}

	auto Application::GetApplicationID() -> ApplicationID
	{
		return main->_id;
	}

	auto Application::GetEnvironmentInfo() -> EnvironmentInfo
	{
		return main->_env;
	}
}