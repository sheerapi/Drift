#include "styles/TransitionFunction.h"

namespace Drift::Styling
{
    void CubicEasingFunction::Update(float delta, Animation animation)
    {
		float t = std::min(animation.Elapsed / ((float)animation.Duration / 1000), 1.0F);
		*animation.Value =
			animation.Start + (animation.Target - animation.Start) * _easing.Evaluate(t);
	}

	void Animation::Update(float delta)
    {
		Elapsed += delta;

		if (IsFinished())
		{
			return;
		}

		if (Easing != nullptr)
        {
            Easing->Update(delta, *this);
        }
    }
}