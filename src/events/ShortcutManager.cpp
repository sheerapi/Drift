#include "events/ShortcutManager.h"
#include "core/Application.h" // IWYU pragma: keep
#include "core/Logger.h"
#include "events/InputSystem.h"
#include "utils/StringUtils.h"

namespace Drift
{
	void ShortcutManager::Register(const std::string& name,
								   const std::unordered_set<Keycode>& keys)
	{
		std::unordered_set<int> result;

        for (const auto& key : keys)
        {
            result.insert((int)key);
        }

		shortcuts.push_back({.Keys = result, .Name = name});
	}

    void ShortcutManager::OnKeyPress(Keycode key)
    {
        keys.insert((int)key);
    }

    void ShortcutManager::OnKeyRelease(Keycode key)
    {
		keys.erase((int)key);
	}

    void ShortcutManager::ClearInput()
    {
        keys.clear();
    }

    auto ShortcutManager::CheckShortcuts() -> bool
    {
        bool result = false;

        for (auto& shortcut : shortcuts)
        {
            if (shortcut.Keys == keys)
            {
                result = true;

                dt_coreVerbose("Shortcut {} triggered", shortcut.Name);

                if (Input::currentView != nullptr)
                {
                    Input::currentView->EmitSignal("shortcut." + stringToLower(shortcut.Name));
                }

				if (Input::hoveredElement != nullptr)
				{
					Input::hoveredElement->EmitSignal("shortcut." +
													  stringToLower(shortcut.Name));
				}

				if (Input::focusedElement != nullptr)
				{
					Input::focusedElement->EmitSignal("shortcut." +
													  stringToLower(shortcut.Name));
				}
			}
        }

        return result;
    }
}