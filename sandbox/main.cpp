#include "components/Window.h"
#include "core/Application.h"
#include "core/LayoutEnums.h"
#include "styles/AnimationStyles.h"
#include "styles/LayoutStyles.h"
#include "styles/RenderingStyles.h"
#include "styles/Style.h"
#include "styles/TransitionFunction.h"
#include "utils/Color.h"

using namespace Drift;
using namespace Drift::Styling;

auto main(int argc, const char** argv) -> int
{
	auto* app = new Application("com.drift.sandbox");

	auto window = app->AttachView<Window>("Sandbox");

	auto* easing = new CubicEasingFunction(0.175, 0.885, 0.32, 1.275);

	auto* root = window->GetCurrentActivity()
					 ->AttachRoot(std::make_shared<Element>())
					 ->FlexDirection(Direction::Row)
					 ->Gap(10)
					 ->Padding(10)
					 ->AddStyle<Styling::BackgroundColor>(Color::FromHex(0xFFFFFF));

	auto* container1 =
		root->AddChild<Element>()
			->FlexGrow(1)
			->FlexDirection(Direction::Column)
			->JustifyContent(Justify::SpaceBetween)
			->AddStyle<Styling::TransitionDuration>(500, TimeUnit::Milliseconds)
			->AddStyle<Styling::TransitionEasingFunction>(easing);

	for (int i = 0; i < 5; i++)
	{
		auto* btn =
			container1->AddChild<Element>()
				->FlexGrow(1)
				->AddStyle<Styling::BackgroundColor>(Color::FromHex(0x000000))
				->ZIndex(i)
				->AddStyle<Styling::TransitionDuration>(500, TimeUnit::Milliseconds)
				->AddStyle<Styling::TransitionEasingFunction>(easing);

		btn->On("hover",
				[btn, container1](Event event)
				{
					btn->AddStyle<Styling::BackgroundColor>(Color::FromHex(0x333333));
					container1->GapVertical((float)btn->ZIndex() * 10);
				});

		btn->On("unhover",
				[btn, container1](Event event)
				{
					btn->AddStyle<Styling::BackgroundColor>(Color::FromHex(0x000000));
					container1->GapVertical(0);
				});
	}

	auto* container2 = root->AddChild<Element>()
						   ->FlexGrow(2)
						   ->FlexDirection(Direction::Column)
						   ->Gap(20)
						   ->JustifyContent(Justify::SpaceBetween);

	auto* container3 = container2->AddChild<Element>()
						   ->FlexDirection(Direction::Row)
						   ->JustifyContent(Justify::SpaceBetween);

	for (size_t i = 0; i < 12; i++)
	{
		auto* btn =
			container3->AddChild<Element>()
				->FlexGrow(1)
				->AddStyle<Styling::BackgroundColor>(Color::FromHex(0x000000))
				->Height(50)
				->AddStyle<Styling::TransitionDuration>(500, TimeUnit::Milliseconds)
				->AddStyle<Styling::TransitionEasingFunction>(easing);

		btn->On("hover",
				[btn](Event event) {
					btn->AddStyle<Styling::BackgroundColor>(Color::FromHex(0x333333))
						->Height(150);
				});

		btn->On("unhover",
				[btn](Event event) {
					btn->AddStyle<Styling::BackgroundColor>(Color::FromHex(0x000000))
						->Height(50);
				});
	}

	auto* container4 = container2->AddChild<Element>()
						   ->AddStyle<Styling::BackgroundColor>(Color::FromHex(0x000000))
						   ->FlexGrow(1);

	return app->Present();
}