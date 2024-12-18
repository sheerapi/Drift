#include "events/InputSystem.h"
#include "events/ShortcutManager.h"
#include "magic_enum.hpp"
#include "utils/StringUtils.h"
#include "utils/utf/checked.h"

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
			hoveredElement->EmitSignal("cursor.move", {relPos});
		}

		delete relPos;
	}

	void Input::TriggerMouseClick(MouseButton button, bool clicked)
	{
		if (clicked)
		{
			if (focusedElement != nullptr && hoveredElement != focusedElement)
			{
				focusedElement->EmitSignal("unfocus");
				focusedElement = nullptr;
			}
		}

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

	void Input::TriggerMouseScroll(Vector2 offsets)
	{
		if (currentView != nullptr)
		{
			currentView->EmitSignal("cursor.scroll", &offsets);
		}

		if (hoveredElement != nullptr)
		{
			hoveredElement->EmitSignal("cursor.scroll", {&offsets});
		}
	}

	void Input::TriggerKeypress(Keycode key, bool pressed)
	{
		pressed ? ShortcutManager::OnKeyPress(key) : ShortcutManager::OnKeyRelease(key);

		if (currentView != nullptr)
		{
			if (hoveredElement != nullptr)
			{
				hoveredElement->EmitSignal(
					"key." + std::string((pressed ? "pressed" : "released")), {&key});
				hoveredElement->EmitSignal(
					(pressed ? "pressed." : "released.") +
					stringToLower(std::string(magic_enum::enum_name(key))));
			}

			if (focusedElement != nullptr)
			{
				focusedElement->EmitSignal(
					"key." + std::string((pressed ? "pressed" : "released")), {&key});
				focusedElement->EmitSignal(
					(pressed ? "pressed." : "released.") +
					stringToLower(std::string(magic_enum::enum_name(key))));
			}

			currentView->EmitSignal(
				"key." + std::string((pressed ? "pressed" : "released")), &key);

			currentView->EmitSignal(
				(pressed ? "pressed." : "released.") +
				stringToLower(std::string(magic_enum::enum_name(key))));
		}
	}

	void Input::StartTextInput()
	{
		typing = true;
	}

	auto Input::EndTextInput() -> std::string
	{
		auto text = textTyped;
		typing = false;
		textTyped = "";
		return text;
	}

	auto Input::GetTextInput() -> std::string
	{
		return textTyped;
	}

	void Input::TriggerTextInput(unsigned int codepoint)
	{
		if (!typing)
		{
			return;
		}

		auto oldText = textTyped;

		utf8::append(codepoint, textTyped);
		utf8::replace_invalid(textTyped);

		if (currentView != nullptr)
		{
			currentView->EmitSignal("typed", &oldText);
		}

		if (focusedElement != nullptr)
		{
			focusedElement->EmitSignal("typed", &oldText);
		}
	}

	void Input::Focus(Element* element, bool focus)
	{
		if (focus && element->Focusable())
		{
			if (Input::focusedElement != nullptr)
			{
				if (Input::focusedElement != element)
				{
					Input::focusedElement->EmitSignal("unfocus");
				}
			}

			Input::focusedElement = element;
			Input::focusedElement->EmitSignal("focus");
		}

		if (!focus && Input::focusedElement != nullptr)
		{
			if (Input::focusedElement == element)
			{
				Input::focusedElement = nullptr;
				Input::focusedElement->EmitSignal("unfocus");
			}
		}
	}
}