#include "core/Application.h"
#include "core/View.h"
#include "events/DummyEventLoop.h"

auto main(int argc, const char** argv) -> int
{
	auto* app = new Drift::Application("com.drift.sandbox");
	app->AttachEventLoop<Drift::Events::DummyEventLoop>();

	auto window = app->AttachView<Drift::View>();
	auto root =
		window->GetCurrentActivity()->AttachRoot(std::make_shared<Drift::Element>());

	root->ID("root")->ClassName("bg-neutral-950 text-slate-100");

	app->GetEventLoop()->PrintViewTree();

	return app->Present();
}