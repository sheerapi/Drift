#include "styles/AnimationScheduler.h"
#include "utils/Time.h"

namespace Drift::Styling
{
	void AnimationScheduler::Submit(const Animation& animation)
	{
		animatables.push_back(animation);
	}

	void AnimationScheduler::Update()
	{
		for (auto& anim : animatables)
		{
			anim.Update((float)Time::GetDeltaTime());
		}

		animatables.erase(std::remove_if(animatables.begin(), animatables.end(),
										 [](const Animation& anim)
										 { return anim.IsFinished(); }),
						  animatables.end());
	}

	void AnimationScheduler::AnimateValue(float* value, float end, int duration,
										  EasingFunction* function)
	{
		Animation anim;
		anim.Start = *value;
		anim.Duration = duration;
		anim.Value = value;
		anim.Target = end;
		anim.Easing = function;

		Submit(anim);
	}

	void AnimationScheduler::AnimateValue(float* value, float start, float end, int duration,
										  EasingFunction* function)
	{
		Animation anim;
		anim.Start = start;
		anim.Duration = duration;
		anim.Value = value;
		anim.Target = end;
		anim.Easing = function;

		Submit(anim);
	}
}