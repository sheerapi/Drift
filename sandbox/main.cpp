#include "core/Application.h"
#include "components/Window.h"

auto main(int argc, const char** argv) -> int
{
	auto* app = new Drift::Application("com.drift.sandbox");

	auto window = app->AttachView<Drift::Window>("Sandbox");

	auto root =
		window->GetCurrentActivity()->AttachRoot(std::make_shared<Drift::Element>());

	root->AddChild<Drift::Element>()->Width(100)->Height(100);

	Drift::Application::ForceGlobalLayoutRefresh();
	app->GetEventLoop()->PrintViewTree();

	return app->Present();
}