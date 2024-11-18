#include "core/Application.h"
#include "core/View.h"
#include "events/DummyEventLoop.h"
#include "utils/LibraryManager.h"

auto main(int argc, const char** argv) -> int
{
	auto* app = new Drift::Application("com.drift.sandbox");
	app->AttachEventLoop<Drift::Events::DummyEventLoop>();

	auto lib = Drift::LibraryManager::LoadLibrary("libm.so");
	double (*cosFunc)(double);
	cosFunc = (double (*)(double))lib->GetSymbol("cos");
	dt_info("{}", cosFunc(6));

	auto window = app->AttachView<Drift::View>();
	app->GetEventLoop()->PrintViewTree();

	return app->Present();
}