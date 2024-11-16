#pragma once

namespace Drift
{
	class EventLoop
	{
	public:
		virtual void Start() {};
		virtual void Tick() = 0;
		virtual ~EventLoop() = default;

		virtual auto IsRunning() -> bool = 0;
	};
}