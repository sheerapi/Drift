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

		GetCurrentActivity()->SetStatus(Activity::Status::Paused);
		GetCurrentActivity()->OnDestroy();
		GetCurrentActivity()->HandleEffects();
		DestroyedActivities.push_back(GetCurrentActivity());
		Activities.pop_back();

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
			return;
		}

		GetCurrentActivity()->SetStatus(Activity::Status::Active);
		GetCurrentActivity()->OnResume();
	}

	void View::PrintElementTree()
	{
		auto bounds = GetBoundingBox();

		dt_coreDebug("   {} [enabled = {} ({}x{} @ {},{})]", getNamespaceFreeName(dt_type(*this)),
					 _enabled, bounds.Width, bounds.Height, bounds.X, bounds.Y);

		GetCurrentActivity()->PrintElementTree();
	}

	auto View::AddActivity(const std::shared_ptr<Activity>& activity)
		-> std::shared_ptr<Activity>
	{
		if (!Activities.empty())
		{
			GetCurrentActivity()->SetStatus(Activity::Status::Paused);
			GetCurrentActivity()->OnPause();
		}

#ifdef DEBUG
		auto old =
			Activities.empty() ? "No Activity" : GetCurrentActivity()->GetActivityID();
#endif

		Activities.push_back(activity);
		GetCurrentActivity()->OnCreate();
		GetCurrentActivity()->OnResume();
		GetCurrentActivity()->SetStatus(Activity::Status::Active);
		GetCurrentActivity()->SetContainingView(this);
		GetCurrentActivity()->HandleEffects();

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

		Activities[Activities.size() - 1] = activity;
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

	void View::ForceLayoutRefresh()
	{
		GetCurrentActivity()->ForceLayoutRefresh();
	}

	auto View::ReplaceActivity(Activity* activity) -> std::shared_ptr<Activity>
	{
		return ReplaceActivity(std::shared_ptr<Activity>(activity));
	}

	auto View::GetCurrentActivity() -> std::shared_ptr<Activity>
	{
		return Activities[Activities.size() - 1];
	}

	auto View::AttachRoot(const std::shared_ptr<Element>& root) -> std::shared_ptr<Element>
	{
		GetCurrentActivity()->AttachRoot(root);
		return root;
	}

	auto View::AttachRoot() -> std::shared_ptr<Element>
	{
		return AttachRoot(std::make_shared<Element>());
	}
}