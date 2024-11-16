#pragma once
#include "EventLoop.h"

namespace Drift::Events
{
	class DummyEventLoop : public EventLoop
	{
		void Tick() override;
		auto IsRunning() -> bool override;
	};
}