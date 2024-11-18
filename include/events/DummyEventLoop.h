#pragma once
#include "EventLoop.h"
#include "core/Macros.h"

namespace Drift::Events
{
	class dt_api DummyEventLoop : public EventLoop
	{
		void Start() override;
		void Tick() override;
		auto IsRunning() -> bool override;

	private:
		bool _running{true};
	};
}