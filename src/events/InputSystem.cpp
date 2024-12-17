#include "events/InputSystem.h"

namespace Drift
{
	void Input::RecalculateState()
	{
		if (currentView == nullptr)
		{
			hoveredElement = nullptr;
			return;
		}

        auto* prevHover = hoveredElement;

		hoveredElement = Element::FindDeepestMatch(
			currentView->GetCurrentActivity()->Root.get(), mousePosition);

        if (prevHover != hoveredElement)
        {
            prevHover->EmitSignal("unhover");
			hoveredElement->EmitSignal("hover");
		}
	}
}