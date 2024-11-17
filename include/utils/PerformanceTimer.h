#pragma once
#ifdef DEBUG
#	include <chrono>
#	include <string>

namespace Drift::Internals
{
	class PerformanceTimer
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
		auto stopwatch_##__PRETTY_FUNCTION__ =                                           \
			Drift::Internals::PerformanceTimer(__PRETTY_FUNCTION__);

#else
#	define dt_stopwatch()
#endif