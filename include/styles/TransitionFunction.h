#pragma once
#include "core/Macros.h"
#include "utils/CubicBezier.h"

namespace Drift::Styling
{
    struct EasingFunction;

	struct dt_api Animation
	{
	public:
		float* Value;
		float Start;
		float Target;
		long Duration; // expected to be in ms
		float Elapsed{0};
		EasingFunction* Easing;

		[[nodiscard]] inline auto IsFinished() const -> bool
		{
			return Elapsed >= ((float)Duration / 1000);
		}

		virtual void Update(float delta);
	};

	struct dt_api EasingFunction
    {
    public:
		virtual void Update(float delta, Animation animation) {};
	};

	struct dt_api CubicEasingFunction : public EasingFunction
	{
    public:
		CubicEasingFunction(float x1, float y1, float x2, float y2)
			: _easing(x1, y1, x2, y2)
		{
        }

        void Update(float delta, Animation animation) override;

    private:
        CubicBezier _easing;
    };
}