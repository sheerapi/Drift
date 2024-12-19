#pragma once
#include "core/Macros.h"
#include "core/View.h"
#include "events/Keycode.h"
#include "utils/Vector2.h"

namespace Drift
{
	enum class MouseButton
	{
		Left,
		Right,
		Middle,
		None = -1
	};

	class dt_api Input
	{
	public:
		inline static View* currentView{nullptr};
		inline static Vector2 mousePosition;
		inline static Element* hoveredElement{nullptr};
		inline static Element* focusedElement{nullptr};

		static void RecalculateState();
		static void TriggerMouseMove(Vector2 pos);
		static void TriggerMouseScroll(Vector2 offset);
		static void TriggerMouseClick(MouseButton button, bool clicked);
		static void TriggerKeypress(Keycode key, bool pressed, bool repeat);
		static void TriggerTextInput(unsigned int codepoint);

		static void StartTextInput(bool multi = false);
		static auto EndTextInput() -> std::string;
		static auto GetTextInput() -> std::string;

		static void Focus(Element* element, bool focus = true);
		static void Paste(const std::string& str);

		static void Reset();

	private:
		inline static bool typing{false};
		inline static bool multiLine{false};
		inline static Element* clickedElement{nullptr};
		inline static int cursorPos;
		inline static std::string textTyped;

		inline static MouseButton lastButton;
		inline static Keycode lastKeycode;
		
		inline static void HandleTypeKey(Keycode key);
	};
}