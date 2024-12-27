#include "components/FadeActivity.h"
#include "components/Text.h"
#include "components/Window.h"
#include "core/Application.h"
#include "core/LayoutEnums.h"
#include "styles/AnimationStyles.h"
#include "styles/RenderingStyles.h"
#include "styles/Style.h"
#include "styles/TransitionFunction.h"
#include "styles/TypographyStyles.h"
#include "utils/Color.h"

using namespace Drift;
using namespace Drift::Styling;

auto main(int argc, const char** argv) -> int
{
	auto* app = new Application("com.drift.sandbox");

	auto window = app->AttachView<Window>("Sandbox");

	auto* root = window->GetCurrentActivity()
					 ->AttachRoot(std::make_shared<Element>())
					 ->FlexDirection(Direction::Row)
					 ->Gap(10)
					 ->Padding(10)
					 ->AddStyle<BackgroundColor>(Color::FromHex(0xFFFFFF))
					 ->AddStyle<FontSize>(32);

	root->AddChild<Text>("Hello ❤️❤️🐸")
		->AddStyle<BackgroundColor>(Color::FromHex(0xFF0000));

	return app->Present();
}