#pragma once
#include "../core/Macros.h"
#include "../core/View.h"
#include <memory>
#include <vector>

namespace Drift::Events
{
	class dt_api EventLoop
	{
	public:
		virtual void Start() {};
		virtual void Tick() = 0;
		virtual void HandleView(const std::shared_ptr<View>& view) {};
		void Update();
		virtual ~EventLoop() = default;

		virtual auto IsRunning() -> bool
		{
			return Running;
		}

		inline void PushView(const std::shared_ptr<View>& view)
		{
			Views.push_back(view);
		}

		inline auto GetViews() -> std::vector<std::shared_ptr<View>>
		{
			return Views;
		}

		void PrintViewTree();
		void ForceLayoutRefresh();

	protected:
		std::vector<std::shared_ptr<View>> Views;
		bool Running{true};
	};
}