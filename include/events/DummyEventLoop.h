#pragma once
#include "EventLoop.h"

namespace Drift::Events
{
	class DummyEventLoop : public EventLoop
	{
		void Start() override;
		void Tick() override;
		auto IsRunning() -> bool override;

	private:
		bool _running{true};
	};
}