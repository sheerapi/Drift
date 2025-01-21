#pragma once
#include "../core/Element.h"
#include "../core/Macros.h"
#include "components/activities/ActivityEffect.h"
#include "events/Observable.h"
#include "styles/AnimationStyles.h"
#include "styles/TransitionFunction.h"
#include <utility>

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
		Activity(std::string name = "");

		auto GetActivityID() -> std::string;

		virtual void OnCreate() {};
		virtual void OnPause() {};
		virtual void OnResume() {};
		virtual void OnDestroy();

		virtual void BeginDraw() {};
		virtual void EndDraw() {};
		virtual void Tick() {};

		void Update();
		void Render();

		void ForceLayoutRefresh();

		auto AttachRoot(const std::shared_ptr<Element>& root) -> std::shared_ptr<Element>;
		auto AttachRoot(Element* root) -> std::shared_ptr<Element>;
		auto AttachRoot() -> std::shared_ptr<Element>;

		template<typename T, typename... Args>
		auto AttachRoot(Args&&... args) -> std::shared_ptr<T>
		{
			typeCheck<Element, T>();
			return std::dynamic_pointer_cast<T>(AttachRoot(std::make_shared<T>(args...)));
		}

		void Finish();
		void PrintElementTree();
		void HandleEffects();

		void SetStatus(Status status);
		auto SetName(const std::string& name) -> Activity*;
		void SetContainingView(View* view);

		auto GetStatus() -> Status;
		auto GetContainingView() -> View*;

		auto CloneRoot() -> std::shared_ptr<Element>;

		template <typename T, typename... Args>
		auto AddEffect(Args&&... args) -> Activity*
		{
			typeCheck<Components::Activities::ActivityEffect, T>();
			auto effect = std::make_shared<T>(std::forward<Args>(args)...);
			_effects.push_back(effect);

			std::sort(_effects.begin(), _effects.end(),
					  [](auto a, auto b) { return a->GetPriority() > b->GetPriority(); });

			return this;
		}

		auto GetEasing() -> Styling::EasingFunction*;
		auto GetEasingDuration() const -> int;

		auto SetEasing(Styling::EasingFunction* easing) -> Activity*;
		auto SetEasingDuration(int duration,
							   Styling::TimeUnit unit = Styling::TimeUnit::Milliseconds)
			-> Activity*;

		auto GetRoot() -> std::shared_ptr<Element>;

	protected:
		std::shared_ptr<Element> Root;

	private:
		Status _status{Activity::Status::Active};
		View* _containingView{nullptr};
		std::string _name;
		std::vector<std::shared_ptr<Components::Activities::ActivityEffect>> _effects;
		Styling::EasingFunction* _easing{
			new Styling::CubicEasingFunction(0.19, 1, 0.22, 1)};
		int _easingDuration{350};

		friend class Input;
	};
}