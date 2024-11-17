#include "core/Application.h"
#include "core/View.h"
#include "events/DummyEventLoop.h"

auto main(int argc, const char** argv) -> int {
    auto* app = new Drift::Application("com.drift.sandbox");
    app->AttachEventLoop<Drift::Events::DummyEventLoop>();

    auto window = app->AttachView<Drift::View>();
    app->GetEventLoop()->PrintViewTree();

    window->NavigateBack();

    return app->Present();
}