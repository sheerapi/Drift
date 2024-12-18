#include "events/Observable.h"
#include "utils/StringUtils.h"
#include "core/Logger.h"

namespace Drift::Events
{
	void Observable::On(std::string signal, const SignalHandler& handler)
	{
		_handlers[stringToLower(std::move(signal))].push_back(handler);
	}

	void Observable::Remove(std::string signal)
	{
		signal = stringToLower(std::move(signal));

		if (!_handlers.contains(signal))
		{
			dt_coreWarn("Tried to remove handlers of signal \"{}\", but no handlers "
						"of that signal could be found",
						signal);

			return;
		}

		_handlers[signal].clear();
	}

	void Observable::Remove(std::string signal, SignalHandler& handler)
	{
		signal = stringToLower(std::move(signal));

		if (!_handlers.contains(signal))
		{
			dt_coreWarn("Tried to remove a handler of signal \"{}\", but no handlers "
						"of that signal could be found",
						signal);

			return;
		}

		_handlers[signal].erase(std::remove_if(_handlers[signal].begin(),
										 _handlers[signal].end(),
										 [=](auto itr) { return itr = handler; }), _handlers[signal].end());
	}

	void Observable::EmitSignal(std::string signal, void* data)
	{
		signal = stringToLower(signal);

		if (!_handlers.contains(signal))
		{
			return;
		}

		for (const auto& handler : _handlers[signal])
		{
			try
			{
				handler(data);
			}
			catch (const std::exception& e)
			{
				dt_coreError("Exception ocurred while handling signal \"{}\": {}", signal,
							 e.what());
			}
			catch (...)
			{
				dt_coreFatal("An unknown exception ocurred while handling signal "
							 "\"{}\" that will be re-throwed.");
				throw "Unknown";
			}

			// just to be sure lol
		}
	}
}