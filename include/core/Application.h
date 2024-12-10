#pragma once
#include "../core/ApplicationInfo.h"
#include "../core/Logger.h"
#include "../events/EventLoop.h"
#include <memory>
#include <string>

namespace Drift
{
	class dt_api Application
	{
	public:
		inline static Application* main{nullptr};

		Application(const std::string& appId);
		auto Present() -> int;
		auto GetEventLoop() -> std::shared_ptr<Events::EventLoop>;
		static auto GetApplicationID() -> ApplicationID;
		static auto GetEnvironmentInfo() -> EnvironmentInfo;

		template <typename T> void AttachEventLoop()
		{
			if (_presented)
			{
				dt_coreError("Tried to attach a new event loop!");
				return;
			}

			_eventLoop = std::make_shared<T>();
		}

		template <typename T, typename... Args>
		auto AttachView(Args&&... args) -> std::shared_ptr<T>
		{
			auto view = std::make_shared<T>(args...);
			if (_eventLoop == nullptr)
			{
				dt_coreError("No event loop attached!");
			}
			_eventLoop->PushView(view);
			return view;
		}

	private:
		ApplicationID _id;
		EnvironmentInfo _env;
		std::shared_ptr<Events::EventLoop> _eventLoop{nullptr};
		bool _presented{false};
	};
}