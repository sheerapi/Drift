#include "core/Application.h"
#include "core/ApplicationInfo.h"
#include "utils/ConfigManager.h"
#include "utils/Demangle.h" // IWYU pragma: keep
#include "utils/LibraryManager.h"
#include "utils/PerformanceTimer.h"
#include "utils/Time.h"
#include "core/Scheduler.h"

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
		_env = new EnvironmentInfo();

		dt_stopwatch(); // Not really accurate but still lol

		ConfigManager::Init();
		LibraryManager::Init();

		dt_coreInfo("Initialized \"{}\"", _id.GetCompoundID());
		Time::Update();
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

		Scheduler::Shutdown();

		delete this; // suicide
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
		return *(main->_env);
	}

	void Application::ForceGlobalLayoutRefresh()
	{
		if (!main->_eventLoop)
		{
			dt_coreError("No event loop attached!");
			return;
		}
		main->_eventLoop->ForceLayoutRefresh();
	}

	Application::~Application()
	{
		ConfigManager::Write();
		delete _env;
	}
}