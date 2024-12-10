#pragma once
#include "../core/Macros.h"
#include <functional>
#include <string>
#include <unordered_map>
#include <vector>

namespace Drift::Events
{
	/**
	 * @brief Simple wrapper around a function pointer that can take in a void pointer as
	 * data
	 */
	using SignalHandler = std::function<void(void*)>;

	class dt_api Observable
	{
	public:
		/**
		 * @brief Attaches a signal handler to a specific signal so it gets called
		 * everytime it's emitted
		 *
		 * @param signal Signal to attach the handler to
		 * @param handler Callback function that must take data based on the event (some
		 * have data, others nullptr)
		 * @return T* Same instance of the class, for chaining
		 */
		void On(std::string signal, const SignalHandler& handler);

		/**
		 * @brief Tries to remove every handler for a specific signal
		 *
		 * @param signal Signal to remove the handlers from
		 * @return T* Same instance of the class, for chaining
		 */
		void Remove(std::string signal);

		/**
		 * @brief Remove a specific signal handler from a signal
		 *
		 * @param signal Signal to remove the handler from
		 * @param handler Handler to remove
		 * @return T* Same instance of the class, for chaining
		 */
		void Remove(std::string signal, SignalHandler& handler);

		/**
		 * @brief Removes *every* signal and their handlers
		 *
		 * @return T* Same instance of the class, for chaining
		 */
		inline void RemoveAll()
		{
			_handlers.clear();
		}

		/**
		 * @brief Emit a signal, calling every attached callback function for that signal
		 *
		 * @param signal Signal to emit
		 * @param data Data to pass to the handler, can be nullptr
		 */
		void EmitSignal(std::string signal, void* data = nullptr);

	private:
		std::unordered_map<std::string, std::vector<SignalHandler>> _handlers;
	};
}