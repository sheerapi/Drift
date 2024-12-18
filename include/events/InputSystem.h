#pragma once
#include "core/Macros.h"
#include "core/View.h"
#include "utils/Vector2.h"

namespace Drift
{
	enum class MouseButton
	{
		Left,
		Right,
		Middle
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
	};
}