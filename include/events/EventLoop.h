#pragma once
#include "core/View.h"
#include <memory>
#include <vector>

namespace Drift
{
	class EventLoop
	{
	public:
		virtual void Start() {};
		virtual void Tick() = 0;
		virtual ~EventLoop() = default;

		virtual auto IsRunning() -> bool = 0;

		inline void PushView(const std::shared_ptr<View>& view)
		{
			Views.push_back(view);
		}

	protected:
		std::vector<std::shared_ptr<View>> Views;
	};
}