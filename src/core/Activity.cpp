#include "core/Activity.h"
#include <ranges>
#include "core/Application.h"
#include "core/Scheduler.h"
#include "styles/Style.h"

namespace Drift
{
	Activity::Activity(std::string name)
	{
		Root = std::make_shared<Element>();
		_name = std::move(name);
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
		return Application::GetApplicationID().GetCompoundID() + "." +
			   (_name.empty() ? getNamespaceFreeName(dt_type(*this)) : _name);
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
		for (auto& effect : _effects)
		{
			effect->BeginDraw(this);
		}

		BeginDraw();
		Root->Render();
		EndDraw();

		for (auto & _effect : std::ranges::reverse_view(_effects))
		{
			_effect->EndDraw(this);
		}
	}

	auto Activity::CloneRoot() -> std::shared_ptr<Element>
	{
		return {Root};
	}

	auto Activity::GetEasing() -> Styling::EasingFunction*
	{
		return _easing;
	}

	auto Activity::GetEasingDuration() const -> int
	{
		return _easingDuration;
	}

	auto Activity::SetEasing(Styling::EasingFunction* easing) -> Activity*
	{
		_easing = easing;
		return this;
	}

	auto Activity::SetEasingDuration(int duration, Styling::TimeUnit unit) -> Activity*
	{
		auto result = duration;

		switch (unit)
		{
		case Styling::TimeUnit::Seconds:
			result *= 1000;
			break;
		case Styling::TimeUnit::Minutes:
			result *= 60000;
			break;
		case Styling::TimeUnit::Hours:
			result *= 3600000;
			break;
		default:
			break;
		};

		_easingDuration = result;
		return this;
	}

	void Activity::HandleEffects()
	{
		if (_effects.empty())
		{
			return;
		}

		if (GetStatus() == Status::Active)
		{
			for (auto& effect : _effects)
			{
				effect->Present(this);
			}
		}
		else
		{
			dt_setTimeout([this]() { Finish(); }, _easingDuration);

			for (auto& effect : _effects)
			{
				effect->Shutdown(this);
			}
		}
	}

	void Activity::OnDestroy()
	{
		if (_effects.empty())
		{
			Finish();
		}
	}
}