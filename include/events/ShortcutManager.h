#pragma once
#include "core/Macros.h"
#include "events/Keycode.h"
#include <string>
#include <unordered_set>
#include <vector>

namespace Drift
{
	struct dt_api Shortcut
	{
	public:
		std::unordered_set<int> Keys;
		std::string Name;
	};

	class dt_api ShortcutManager
	{
	public:
		static void Register(const std::string& name,
							 const std::unordered_set<Keycode>& keys);
		static void ClearInput();
		static auto CheckShortcuts() -> bool;

	private:
		inline static std::vector<Shortcut> shortcuts;
		inline static std::unordered_set<int> keys;

		static void OnKeyPress(Keycode key);
		static void OnKeyRelease(Keycode key);

		friend class Input;
	};
}