#include "core/Application.h"
#include "components/Window.h"

auto main(int argc, const char** argv) -> int
{
	auto* app = new Drift::Application("com.drift.sandbox");

	auto window = app->AttachView<Drift::Window>("Sandbox");

	auto root =
		window->GetCurrentActivity()->AttachRoot(std::make_shared<Drift::Element>());

	root->ID("root")->ClassName("bg-neutral-950 text-slate-100");

	Drift::Application::ForceGlobalLayoutRefresh();
	app->GetEventLoop()->PrintViewTree();

	return app->Present();
}