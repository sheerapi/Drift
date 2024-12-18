#include "events/InputSystem.h"
#include "magic_enum.hpp"
#include "utils/StringUtils.h"

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
			if (prevHover != nullptr)
			{
				prevHover->EmitSignal("unhover");
			}

			if (hoveredElement != nullptr)
			{
				hoveredElement->EmitSignal("hover");
			}
		}
	}

	void Input::TriggerMouseMove(Vector2 pos)
	{
		auto* relPos = new Vector2((float)pos.X - Input::mousePosition.X,
								   (float)pos.Y - Input::mousePosition.Y);

		Input::mousePosition = {(float)pos.X, (float)pos.Y};
		Input::RecalculateState();

		if (currentView != nullptr)
		{
			currentView->EmitSignal("cursor.move", relPos);
		}

		if (hoveredElement != nullptr)
		{
			hoveredElement->EmitSignal("cursor.move", relPos);
		}

		delete relPos;
	}

	void Input::TriggerMouseClick(MouseButton button, bool clicked)
	{
		if (currentView != nullptr)
		{
			if (hoveredElement != nullptr)
			{
				if (button == MouseButton::Left)
				{
					hoveredElement->EmitSignal(clicked ? "click" : "unclick");
				}

				hoveredElement->EmitSignal(
					(clicked ? "click." : "unclick.") +
					stringToLower(std::string(magic_enum::enum_name(button))));
			}

			if (button == MouseButton::Left)
			{
				currentView->EmitSignal(clicked ? "click" : "unclick");
			}

			currentView->EmitSignal(
				(clicked ? "click." : "unclick.") +
				stringToLower(std::string(magic_enum::enum_name(button))));
		}
	}
}