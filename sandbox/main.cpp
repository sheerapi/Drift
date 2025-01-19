#include "components/Window.h"
#include "components/activities/ActivityEffect.h"
#include "core/Application.h"
#include "core/LayoutEnums.h"
#include "styles/AnimationStyles.h"
#include "styles/RenderingStyles.h"
#include "styles/Style.h"
#include "styles/TransitionFunction.h"
#include "utils/Color.h"

using namespace Drift;
using namespace Drift::Styling;
using namespace Drift::Components;

auto main(int argc, const char** argv) -> int
{
	bool clicked1;

	auto* app = new Application("com.drift.sandbox");

	auto window = app->AttachView<Window>("Sandbox");

	auto* easing = new CubicEasingFunction(0.175, 0.885, 0.32, 1.1);

	

	return app->Present();
}