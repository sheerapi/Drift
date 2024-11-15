#include "core/Application.h"

auto main(int argc, const char** argv) -> int {
    auto* app = new Drift::Application("com.drift.sandbox");

    return app->Present();
}