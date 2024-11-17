#include "core/View.h"
#include "core/Activity.h"
#include "core/Logger.h"
#include "utils/Demangle.h"

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

		GetCurrentActivity()->SetStatus(Activity::Status::Destroyed);
		Activities.pop();

		// If we closed every activity, close this View
		if (Activities.empty())
		{
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

		Activities.push(activity);
		GetCurrentActivity()->OnCreate();
		GetCurrentActivity()->SetStatus(Activity::Status::Active);
		GetCurrentActivity()->SetContainingView(this);

		return GetCurrentActivity();
	}

	auto View::AddActivity(Activity* activity) -> std::shared_ptr<Activity>
	{
		return AddActivity(std::shared_ptr<Activity>(activity));
	}

	auto View::ReplaceActivity(const std::shared_ptr<Activity>& activity)
		-> std::shared_ptr<Activity>
	{
		Activities.top() = activity;
		GetCurrentActivity()->OnCreate();
		GetCurrentActivity()->SetStatus(Activity::Status::Active);
		GetCurrentActivity()->SetContainingView(this);

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