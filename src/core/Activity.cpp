#include "core/Activity.h"
#include "core/Application.h"
#include "styles/Style.h"

namespace Drift
{
	Activity::Activity()
	{
		Root = std::make_shared<Element>();
	}

	void Activity::Finish()
	{
		if (_status != Status::Paused)
		{
			_containingView->NavigateBack();
		}
		else
		{
			_status = Status::Destroyed;
		}
	}

	auto Activity::GetActivityID() -> std::string
	{
		return Application::GetApplicationID().GetCompoundID() + "." + (_name.empty()
				   ? getNamespaceFreeName(dt_type(*this))
				   : _name);
	}

	auto Activity::SetName(const std::string& name) -> Activity*
	{
		_name = name;
		return this;
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
			Root->Width(Styling::Value(_containingView->GetBoundingBox().Width));
			Root->Height(Styling::Value(_containingView->GetBoundingBox().Height));
		}

		Root->Start();
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

	auto Activity::GetStatus() -> Activity::Status
	{
		return _status;
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
			Root->Width(Styling::Value(_containingView->GetBoundingBox().Width));
			Root->Height(Styling::Value(_containingView->GetBoundingBox().Height));
		}

		Tick();
		Root->Tick();
	}

	void Activity::Render()
	{
		BeginDraw();
		Root->Render();
		EndDraw();
	}

	auto Activity::CloneRoot() -> std::shared_ptr<Element>
	{
		return {Root};
	}
}