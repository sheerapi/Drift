#include "core/Activity.h"
#include "core/Application.h"

namespace Drift
{
	Activity::Activity()
	{
		Root = std::make_shared<Element>();
	}

	void Activity::Finish()
	{
		_containingView->NavigateBack();
	}

	auto Activity::GetActivityID() -> std::string
	{
		return Application::GetApplicationID().GetCompoundID() + "." +
			   getNamespaceFreeName(dt_type(*this));
	}

	void Activity::PrintElementTree()
	{
		dt_coreDebug("      {} [ status = {}, view = {} ]", GetActivityID(), (int)_status,
					 (void*)_containingView);

		Root->DebugPrint(3);
	}

	auto Activity::AttachRoot(const std::shared_ptr<Element>& root) -> std::shared_ptr<Element>
	{
		Root = root;
		return root;
	}

	void Activity::SetStatus(Status status)
	{
		_status = status;

		switch (_status)
		{
		case Status::Active:
			OnResume();
			break;

		case Status::Paused:
			OnPause();
			break;

		case Status::Destroyed:
			OnDestroy();
			break;
		}
	}

	void Activity::SetContainingView(View* view)
	{
		_containingView = view;
	}
}