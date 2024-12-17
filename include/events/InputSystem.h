#pragma once
#include "core/Macros.h"
#include "core/View.h"

namespace Drift
{
    class dt_api Input
    {
    public:
        inline static View* currentView{nullptr};
    };
}