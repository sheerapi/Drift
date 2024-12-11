#include "core/Application.h"
#include "components/Window.h"

auto main(int argc, const char** argv) -> int
{
	auto* app = new Drift::Application("com.drift.sandbox");

	auto window = app->AttachView<Drift::Window>("Sandbox");
	auto window2 = app->AttachView<Drift::Window>("Sandbox2");
	window2->DependsOn(window);

	auto root =
		window->GetCurrentActivity()->AttachRoot(std::make_shared<Drift::Element>());

	root->ID("root")->ClassName("bg-neutral-950 text-slate-100");

	app->GetEventLoop()->PrintViewTree();

	return app->Present();
}