#pragma once
#include "core/Macros.h"
#include "core/View.h"
#include "utils/Vector2.h"

namespace Drift
{
    class dt_api Input
    {
    public:
        inline static View* currentView{nullptr};
        inline static Vector2 mousePosition;
        inline static Element* hoveredElement{nullptr};
        inline static Element* focusedElement{nullptr};

        static void RecalculateState();
    };
}