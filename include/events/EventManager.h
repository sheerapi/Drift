#pragma once
#include "../core/Macros.h"
#include <functional>
#include <mutex>
#include <string>
#include <unordered_map>
#include <vector>

namespace Drift::Events
{
	using EventListener = std::function<void(void*)>;

	class dt_api EventManager
	{
	public:
		static void TriggerEvent(const std::string& name, void* data = nullptr);

		static void AddListener(const std::string& name, const EventListener& callback);
		static void RemoveListener(const std::string& name);

		static void RemoveAll();

	private:
		inline static std::unordered_map<std::string, std::vector<EventListener>>
			listeners;
		inline static std::mutex eventMutex;
	};
}