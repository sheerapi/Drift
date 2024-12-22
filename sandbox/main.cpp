#include "components/Window.h"
#include "core/Application.h"
#include "core/LayoutEnums.h"
#include "styles/AnimationStyles.h"
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

	auto* root = window->GetCurrentActivity()
					 ->AttachRoot(std::make_shared<Element>())
					 ->FlexDirection(FlexDirection::Column)
					 ->Gap(10)
					 ->Padding(10)->Overflow(Overflow::Scroll);

	for (size_t i = 0; i < 40; i++)
	{
		auto* btn =
			root->AddChild<Element>()
				->WidthPercent(100)
				->Height(50)
				->AddStyle<Styling::BackgroundColor>(Color::FromHex(0x282828))
				->AddStyle<Styling::TransitionDuration>(300, TimeUnit::Milliseconds)
				->AddStyle<Styling::TransitionEasingFunction>(
					new CubicEasingFunction(0.19, 1, 0.22, 1));

		btn->On("hover",
				[btn](const Event& e)
				{
					btn->GetStyle<Styling::BackgroundColor>()->ApplyEdits(
						btn, Color::FromHex(0x383838));
				});

		btn->On("unhover",
				[btn](const Event& e)
				{
					btn->GetStyle<Styling::BackgroundColor>()->ApplyEdits(
						btn, Color::FromHex(0x282828));
				});
	}

	return app->Present();
}