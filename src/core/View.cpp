#include "core/View.h"
#include "core/Activity.h"
#include "core/Logger.h"
#include "utils/Demangle.h"

#ifdef DEBUG
#	include "core/Application.h" // IWYU pragma: keep
#endif

namespace Drift
{
	View::View()
	{
		AddActivity<Activity>();
	}

	void View::NavigateBack()
	{
		if (Activities.empty())
		{
			dt_coreError("No activities are currently in the stack!");
			return;
		}

#ifdef DEBUG
		auto old = GetCurrentActivity()->GetActivityID();
#endif

		GetCurrentActivity()->SetStatus(Activity::Status::Destroyed);
		Activities.pop();

#ifdef DEBUG
		auto currentActivity =
			Activities.empty() ? "No Activity" : GetCurrentActivity()->GetActivityID();
#endif

		dt_verbose("View changed activity: {} -> {}", old, currentActivity);

		// If we closed every activity, close this View
		if (Activities.empty())
		{
			Running = false;
			Close();
		}
	}

	void View::PrintElementTree()
	{
		dt_coreDebug("   {} [enabled = {}]", getNamespaceFreeName(dt_type(*this)),
					 _enabled);

		GetCurrentActivity()->PrintElementTree();
	}

	auto View::AddActivity(const std::shared_ptr<Activity>& activity)
		-> std::shared_ptr<Activity>
	{
		if (!Activities.empty())
		{
			GetCurrentActivity()->SetStatus(Activity::Status::Paused);
		}

#ifdef DEBUG
		auto old =
			Activities.empty() ? "No Activity" : GetCurrentActivity()->GetActivityID();
#endif

		Activities.push(activity);
		GetCurrentActivity()->OnCreate();
		GetCurrentActivity()->SetStatus(Activity::Status::Active);
		GetCurrentActivity()->SetContainingView(this);

#ifdef DEBUG
		auto current =
			Activities.empty() ? "No Activity" : GetCurrentActivity()->GetActivityID();
#endif

		dt_verbose("View changed activity: {} -> {}", old, current);

		return GetCurrentActivity();
	}

	auto View::AddActivity(Activity* activity) -> std::shared_ptr<Activity>
	{
		return AddActivity(std::shared_ptr<Activity>(activity));
	}

	auto View::ReplaceActivity(const std::shared_ptr<Activity>& activity)
		-> std::shared_ptr<Activity>
	{
#ifdef DEBUG
		auto old =
			Activities.empty() ? "No Activity" : GetCurrentActivity()->GetActivityID();
#endif

		Activities.top() = activity;
		GetCurrentActivity()->OnCreate();
		GetCurrentActivity()->SetStatus(Activity::Status::Active);
		GetCurrentActivity()->SetContainingView(this);

#ifdef DEBUG
		auto current =
			Activities.empty() ? "No Activity" : GetCurrentActivity()->GetActivityID();
#endif

		dt_verbose("View replaced activity: {} -> {}", old, current);

		return GetCurrentActivity();
	}

	auto View::ReplaceActivity(Activity* activity) -> std::shared_ptr<Activity>
	{
		return ReplaceActivity(std::shared_ptr<Activity>(activity));
	}

	auto View::GetCurrentActivity() -> std::shared_ptr<Activity>
	{
		return Activities.top();
	}
}