#include "events/EventManager.h"
#include "core/Logger.h"
#include "utils/StringUtils.h"

namespace Drift::Events
{
	void EventManager::TriggerEvent(const std::string& name, void* data)
	{
		if (listeners.contains(stringToLower(name)))
		{
			std::lock_guard<std::mutex> lock(eventMutex);

			for (auto& callback : listeners[stringToLower(name)])
			{
				callback(data);
			}
		}
	}

	void EventManager::AddListener(const std::string& name, const EventListener& callback)
	{
		std::lock_guard<std::mutex> lock(eventMutex);
		listeners[stringToLower(name)].push_back(callback);
	}

	void EventManager::RemoveListener(const std::string& name)
	{
		if (listeners.contains(stringToLower(name)))
		{
			std::lock_guard<std::mutex> lock(eventMutex);
			listeners[stringToLower(name)].clear();
		}
		else
		{
			dt_coreError("Event {} not registered!", name);
		}
	}

	void EventManager::RemoveAll()
	{
		std::lock_guard<std::mutex> lock(eventMutex);
		listeners.clear();
	}
}