#include "components/Window.h"
#include "core/Activity.h"
#include "core/Application.h"

using namespace Drift;
using namespace Drift::Styling;

auto main(int argc, const char** argv) -> int
{
	auto* app = new Application("com.drift.sandbox");

	auto window = app->AttachView<Window>("Sandbox");

	auto root = window->AttachRoot();

	return app->Present();
}