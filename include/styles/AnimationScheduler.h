#pragma once
#include "core/Macros.h"
#include "styles/TransitionFunction.h"
#include <vector>

namespace Drift::Styling
{
    class dt_api AnimationScheduler
    {
    public:
        static void Submit(const Animation& animation);
        static void AnimateValue(float* value, float end, int duration, EasingFunction* function);
		static void AnimateValue(float* value, float start, float end, int duration,
								 EasingFunction* function);
		static void Update();

    private:
        inline static std::vector<Animation> animatables;
    };
}