#include "events/InputSystem.h"
#include "events/ShortcutManager.h"
#include "magic_enum.hpp"
#include "utils/StringUtils.h"
#include "utf8/checked.h"

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

	void Input::Reset()
	{
		mousePosition = {0, 0};

		if (clickedElement != nullptr)
		{
			if (lastButton != MouseButton::None)
			{
				clickedElement->EmitSignal("unclick");
				clickedElement->EmitSignal(
					"unclick." +
					stringToLower(std::string(magic_enum::enum_name(lastButton))));
			}

			if (lastKeycode != Keycode::None)
			{
				clickedElement->EmitSignal("key.released", {&lastKeycode});
				clickedElement->EmitSignal(
					"released." +
					stringToLower(std::string(magic_enum::enum_name(lastKeycode))));
			}
		}

		if (currentView != nullptr)
		{
			if (lastButton != MouseButton::None)
			{
				currentView->EmitSignal("unclick");
				currentView->EmitSignal(
					"unclick." +
					stringToLower(std::string(magic_enum::enum_name(lastButton))));
			}

			if (lastKeycode != Keycode::None)
			{
				currentView->EmitSignal("key.released", &lastKeycode);
				currentView->EmitSignal(
					"released." +
					stringToLower(std::string(magic_enum::enum_name(lastKeycode))));
			}
		}

		clickedElement = nullptr;
		hoveredElement = nullptr;
		currentView = nullptr;

		lastButton = MouseButton::None;
		lastKeycode = Keycode::None;
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

		if (clickedElement != nullptr && clickedElement != hoveredElement)
		{
			clickedElement->EmitSignal("unclick");
			clickedElement->EmitSignal(
				"unclick." +
				stringToLower(std::string(magic_enum::enum_name(lastButton))));
			clickedElement = nullptr;
		}

		delete relPos;
	}

	void Input::TriggerMouseClick(MouseButton button, bool clicked)
	{
		lastButton = clicked ? button : MouseButton::None;
		clickedElement = clicked ? hoveredElement : nullptr;

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

	void Input::TriggerKeypress(Keycode key, bool pressed, bool repeat)
	{
		pressed ? ShortcutManager::OnKeyPress(key) : ShortcutManager::OnKeyRelease(key);
		lastKeycode = pressed ? key : Keycode::None;

		if (!typing && ShortcutManager::CheckShortcuts())
		{
			return;
		}

		if (pressed || repeat)
		{
			HandleTypeKey(key);
		}

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

	void Input::StartTextInput(bool multi)
	{
		typing = true;
		multiLine = multi;
	}

	auto Input::EndTextInput() -> std::string
	{
		auto text = textTyped;
		typing = false;
		cursorPos = 0;

		if (currentView != nullptr)
		{
			currentView->EmitSignal("typed.end", &text);
		}

		if (focusedElement != nullptr)
		{
			focusedElement->EmitSignal("typed.end", {&text});
		}

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

		if (ShortcutManager::CheckShortcuts())
		{
			return;
		}

		if (!utf8::internal::is_code_point_valid(codepoint))
		{
			return;
		}

		auto oldText = textTyped;

		utf8::internal::append(codepoint, std::inserter(textTyped, textTyped.begin() + cursorPos));
		cursorPos++;

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

	void Input::HandleTypeKey(Keycode key)
	{
		if (!typing)
		{
			return;
		}

		auto oldText = textTyped;

		bool send = true;

		switch (key)
		{
		case Keycode::Backspace:
		{
			if (textTyped.empty())
			{
				break;
			}

			textTyped.pop_back();
			cursorPos--;
			break;
		}

		case Keycode::Enter:
		{
			if (!multiLine)
			{
				EndTextInput();
				send = false;
			}
			else
			{
				textTyped.insert(textTyped.begin() + cursorPos, '\n');
			}
			break;
		}

		case Keycode::Home:
			cursorPos = 0;
			send = false;
			break;

		case Keycode::End:
			cursorPos = (int)textTyped.size();
			send = false;
			break;

		default:
			send = false;
			break;
		}

		utf8::replace_invalid(textTyped);

		if (send)
		{
			if (currentView != nullptr)
			{
				currentView->EmitSignal("typed", &oldText);
			}

			if (focusedElement != nullptr)
			{
				focusedElement->EmitSignal("typed", &oldText);
			}
		}
	}

	void Input::Paste(const std::string& str)
	{
		if (typing)
		{
			auto oldText = textTyped;

			textTyped += str;
			utf8::replace_invalid(textTyped);
			cursorPos += (int)str.size();

			if (currentView != nullptr)
			{
				currentView->EmitSignal("typed", &oldText);
			}

			if (focusedElement != nullptr)
			{
				focusedElement->EmitSignal("typed", &oldText);
			}
		}
	}
}