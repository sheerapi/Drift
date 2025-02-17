#pragma once
#include "../core/Activity.h"
#include "../core/Macros.h"
#include "events/Observable.h"
#include "graphics/RendererContext.h"
#include "utils/Demangle.h"
#include <memory>
#include <vector>

namespace Drift
{
	class dt_api View : public Events::Observable
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

		[[nodiscard]] inline virtual auto GetBoundingBox() -> BoundingBox
		{
			return {};
		};

		[[nodiscard]] inline auto GetRendererContext() const -> Graphics::RendererContext
		{
			return *RendererContext;
		}

		inline void SetEnabled(bool enabled)
		{
			_enabled = enabled;
		}

		void PrintElementTree();
		void ForceLayoutRefresh();
		void NavigateBack();

		auto AttachRoot(const std::shared_ptr<Element>& root) -> std::shared_ptr<Element>;
		auto AttachRoot() -> std::shared_ptr<Element>;

		template<typename T, typename... Args>
		auto AttachRoot(Args&&... args) -> std::shared_ptr<T>
		{
			typeCheck<Element, T>();
			return std::static_pointer_cast<T>(AttachRoot(std::make_shared<T>(args...)));
		}

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
		std::vector<std::shared_ptr<Activity>> Activities;
		std::vector<std::shared_ptr<Activity>> DestroyedActivities;
		std::shared_ptr<Graphics::RendererContext> RendererContext;
		bool Running{true};

	private:
		bool _enabled{true};

		friend class Activity;
	};
}