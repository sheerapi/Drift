#pragma once

#ifndef DT_NO_GLFW
#include "EventLoop.h"
#include "core/Macros.h"

namespace Drift::Events
{
    class dt_api DesktopEventLoop : public EventLoop
    {
    public:
        void Tick() override;
        void Start() override;
        void HandleView(const std::shared_ptr<View> &view) override;
        ~DesktopEventLoop() override;
    };
}
#endif