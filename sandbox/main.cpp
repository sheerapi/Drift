#include "core/Application.h"
#include "events/DummyEventLoop.h"

auto main(int argc, const char** argv) -> int {
    auto* app = new Drift::Application("com.drift.sandbox");
    app->AttachEventLoop<Drift::Events::DummyEventLoop>();

    return app->Present();
}