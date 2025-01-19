#include "components/Window.h"
#include "components/activities/ActivityEffect.h"
#include "core/Application.h"
#include "styles/RenderingStyles.h"
#include "styles/TransitionFunction.h"

using namespace Drift;
using namespace Drift::Styling;
using namespace Drift::Components;

auto main(int argc, const char** argv) -> int
{
	auto* app = new Application("com.drift.sandbox");

	auto window = app->AttachView<Window>("Sandbox");

	auto* easing = new CubicEasingFunction(0.19, 1, 0.22, 1);

	auto* root = window->AttachRoot()
					 ->AddStyle<BackgroundColor>(Color::FromHex(0xffffff))
					 ->AlignItems(Align::Center)
					 ->JustifyContent(Justify::Center);

	auto* btn = root->AddChild<Element>()
					->PaddingHorizontal(15)
					->PaddingVertical(10)
					->AddStyle<BackgroundColor>(Color::FromHex(0x222222))
					->AddStyle<TransitionEasingFunction>(easing)
					->AddStyle<TransitionDuration>(450, TimeUnit::Milliseconds)
					->BorderRadius(10);

	btn->AddChild<Element>()->Width(65)->Height(16);

	btn->On("hover", [btn](const Event& event)
			{ btn->AddStyle<BackgroundColor>(Color::FromHex(0x333333)); });

	btn->On("unhover", [btn](const Event& event)
			{ btn->AddStyle<BackgroundColor>(Color::FromHex(0x222222)); });

	auto popup = std::make_shared<Activity>("TestModal");
	popup->AddEffect<Activities::SlideEffect>(
		Activities::SlideEffect::Direction::Bottom);

	popup->SetEasing(easing)->SetEasingDuration(500);

	auto root2 = popup->AttachRoot(std::make_shared<Element>())->AlignItems(Align::FlexEnd)->AddChild<Element>();
	root2->AddStyle<BackgroundColor>(Color::FromHex(0xffffff))
		->Height(Value(50, UnitType::Percent))
		->Width(Value(100, UnitType::Percent))
		->AlignItems(Align::Center)
		->JustifyContent(Justify::Center);

	btn->On("click", [popup, window](const Event& event){
		window->AddActivity(popup);
	});

	auto* btn2 = root2->AddChild<Element>()
					->PaddingHorizontal(15)
					->PaddingVertical(10)
					->AddStyle<BackgroundColor>(Color::FromHex(0x222222))
					->AddStyle<TransitionEasingFunction>(easing)
					->AddStyle<TransitionDuration>(450, TimeUnit::Milliseconds)
					->BorderRadius(10);

	btn2->AddChild<Element>()->Width(65)->Height(16);

	btn2->On("hover", [btn2](const Event& event)
			{ btn2->AddStyle<BackgroundColor>(Color::FromHex(0x333333)); });

	btn2->On("unhover", [btn2](const Event& event)
			 { btn2->AddStyle<BackgroundColor>(Color::FromHex(0x222222)); });

	btn2->On("click", [popup, window](const Event& event){
		window->NavigateBack();
	});

	return app->Present();
}