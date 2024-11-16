#pragma once
#include "core/ApplicationInfo.h"
#include "core/Logger.h"
#include "events/EventLoop.h"
#include <memory>
#include <string>

namespace Drift
{
	class Application
	{
	public:
		inline static Application* main{nullptr};

		Application(const std::string& appId);
		auto Present() -> int;

		template<typename T> void AttachEventLoop()
		{
			if (_presented)
			{
				dt_coreError("Tried to attach a new event loop!");
				return;
			}
			
			_eventLoop = std::make_shared<T>();
		}

	private:
		ApplicationID _id;
		EnvironmentInfo _env;
		std::shared_ptr<EventLoop> _eventLoop{nullptr};
		bool _presented{false};
	};
}