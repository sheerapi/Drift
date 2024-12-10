#pragma once
#include "EventLoop.h"

namespace Drift::Events
{
    class DesktopEventLoop : public EventLoop
    {
        void Tick() override;
        void Start() override;
        void HandleView(const std::shared_ptr<View> &view) override;
    };
}