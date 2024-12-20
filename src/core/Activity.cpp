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

	auto Activity::AttachRoot(const std::shared_ptr<Element>& root)
		-> std::shared_ptr<Element>
	{
		Root = root;
		Root->SetContainingActivity(this);
		
		if (_containingView != nullptr)
		{
			Root->Width(_containingView->GetBoundingBox().Width);
			Root->Height(_containingView->GetBoundingBox().Height);
		}
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

	void Activity::ForceLayoutRefresh()
	{
		Root->ForceLayoutRefresh();
	}

	void Activity::SetContainingView(View* view)
	{
		_containingView = view;
	}

	auto Activity::GetContainingView() -> View*
	{
		return _containingView;
	}

	void Activity::Update()
	{
		Root->SetContainingActivity(this);

		if (Root->GetBoundingBox().Width != _containingView->GetBoundingBox().Width ||
			Root->GetBoundingBox().Height != _containingView->GetBoundingBox().Height)
		{
			Root->Width(_containingView->GetBoundingBox().Width);
			Root->Height(_containingView->GetBoundingBox().Height);
		}

		Root->Tick();
	}

	void Activity::Render()
	{
		Root->Render();
	}

	auto Activity::CloneRoot() -> std::shared_ptr<Element>
	{
		return {Root};
	}
}