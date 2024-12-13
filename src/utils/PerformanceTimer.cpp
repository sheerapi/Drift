#include "utils/PerformanceTimer.h"
#ifdef DEBUG
#	include "core/Application.h"

namespace Drift::Internals
{
	PerformanceTimer::PerformanceTimer(const std::string& name)
	{
		if (dt_verboseFlag)
		{
			_name = name;
			_start = std::chrono::high_resolution_clock::now();
		}
	}

	PerformanceTimer::~PerformanceTimer()
	{
		if (dt_verboseFlag)
		{
			auto end = std::chrono::high_resolution_clock::now();
			auto duration =
				std::chrono::duration_cast<std::chrono::microseconds>(end - _start)
					.count();

			if (duration < 1000)
			{
				dt_coreVerbose("{} took {}µs to run", _name,
							std::chrono::duration_cast<std::chrono::microseconds>(end - _start)
								.count());
				return;
			}

			if (duration > 1000 && duration < 1000000)
			{
				dt_coreVerbose(
					"{} took {}ms to run", _name,
					std::chrono::duration_cast<std::chrono::milliseconds>(end - _start)
						.count());
				return;
			}

			if (duration > 1000000)
			{
				dt_coreWarn("{} took {}s to run", _name,
							std::chrono::duration_cast<std::chrono::seconds>(end - _start)
								.count());
			}
		}
	}
}

#endif