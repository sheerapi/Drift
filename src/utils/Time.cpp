#include "utils/Time.h"

namespace Drift
{
    void Time::Update()
    {
		auto now = Clock::now();

		std::chrono::duration<double> frameDuration = now - lastFrameTime;
		deltaTime = frameDuration.count();
		lastFrameTime = now;

		std::chrono::duration<double> elapsedDuration = now - startTime;
		elapsedTime = elapsedDuration.count();

		frameCount++;
		fps = 1.0 / deltaTime;
	}
}