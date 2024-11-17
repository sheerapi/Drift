#pragma once
#include "core/Activity.h"
#include "utils/Demangle.h"
#include <memory>
#include <stack>

namespace Drift
{
	class View
	{
	public:
		View();
		virtual ~View() = default;

		virtual void Present() {};
		virtual void Update() {};
		virtual void Render() {};
		virtual void Close()
		{
			dt_info("Closing view!");
		};

		[[nodiscard]] inline auto IsEnabled() const -> bool
		{
			return _enabled;
		}

		[[nodiscard]] inline auto IsRunning() const -> bool
		{
			return Running;
		}

		inline void SetEnabled(bool enabled)
		{
			_enabled = enabled;
		}

		void PrintElementTree();
		void NavigateBack();

		auto GetCurrentActivity() -> std::shared_ptr<Activity>;

		auto AddActivity(const std::shared_ptr<Activity>& activity)
			-> std::shared_ptr<Activity>;

		template <typename T, typename... Args>
		auto AddActivity(Args&&... args) -> std::shared_ptr<T>
		{
			typeCheck<Activity, T>();
			return AddActivity(std::make_shared<T>(args...));
		}

		auto AddActivity(Activity* activity) -> std::shared_ptr<Activity>;

		template <typename T, typename... Args>
		auto ReplaceActivity(Args&&... args) -> std::shared_ptr<T>
		{
			typeCheck<Activity, T>();
			return ReplaceActivity(std::make_shared<T>(args...));
		}

		auto ReplaceActivity(const std::shared_ptr<Activity>& activity)
			-> std::shared_ptr<Activity>;

		auto ReplaceActivity(Activity* activity) -> std::shared_ptr<Activity>;

	protected:
		std::stack<std::shared_ptr<Activity>> Activities;
		bool Running{true};

	private:
		bool _enabled{true};
	};
}