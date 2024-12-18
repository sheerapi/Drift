#pragma once
#include "core/Macros.h"
#include <chrono>

namespace Drift
{
    class dt_api Time
    {
    public:
        static void Update();

		[[nodiscard]] inline static auto GetDeltaTime() -> double
		{
			return deltaTime;
		}

		[[nodiscard]] inline static auto GetElapsedTime() -> double
		{
			return elapsedTime;
		}

		[[nodiscard]] inline static auto GetFPS() -> double
		{
			return fps;
		}

		[[nodiscard]] inline static auto GetFrameCount() -> unsigned int
		{
			return frameCount;
		}

	private:
		using Clock = std::chrono::steady_clock;
		inline static Clock clock;

		inline static Clock::time_point startTime;
		inline static Clock::time_point lastFrameTime;

		inline static double deltaTime = 0.0;
		inline static double elapsedTime = 0.0;
		inline static double fps = 0.0;
		inline static unsigned long frameCount = 0;
	};
}