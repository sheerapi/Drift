#pragma once
#include "../core/Element.h"
#include "../core/Macros.h"
#include "events/Observable.h"

namespace Drift
{
	class View;

	class dt_api Activity : public Events::Observable
	{
	public:
		enum class Status
		{
			Active,
			Paused,
			Destroyed
		};

		virtual ~Activity() = default;
		Activity();

		auto GetActivityID() -> std::string;

		virtual void OnCreate() {};
		virtual void OnPause() {};
		virtual void OnResume() {};
		virtual void OnDestroy() {};

		void Update();
		void Render();

		void ForceLayoutRefresh();

		auto AttachRoot(const std::shared_ptr<Element>& root) -> std::shared_ptr<Element>;

		void Finish();
		void PrintElementTree();

		void SetStatus(Status status);
		void SetContainingView(View* view);

		auto GetStatus() -> Status;
		auto GetContainingView() -> View*;

		auto CloneRoot() -> std::shared_ptr<Element>;

	protected:
		std::shared_ptr<Element> Root;

	private:
		Status _status{Activity::Status::Active};
		View* _containingView;
	};
}