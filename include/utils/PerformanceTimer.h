#pragma once
#ifdef DEBUG
#	include "../core/Macros.h"
#	include <chrono>
#	include <string>

namespace Drift::Internals
{
	class dt_api PerformanceTimer
	{
	public:
		PerformanceTimer(const std::string& name);
		~PerformanceTimer();

	private:
		std::string _name;
		std::chrono::high_resolution_clock::time_point _start;
	};
}

#	define dt_stopwatch()                                                               \
		auto stopwatch_func = Drift::Internals::PerformanceTimer(__FUNCTION__);

#else
#	define dt_stopwatch()
#endif