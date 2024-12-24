#pragma once
#include "core/Activity.h"
#include "core/Macros.h"
#include "styles/TransitionFunction.h"
#include "utils/Color.h"

namespace Drift::Components
{
	class dt_api FadeActivity : public Activity
	{
	public:
		void BeginDraw() override;
		void EndDraw() override;

		void OnResume() override;
		void OnDestroy() override;

	private:
		Color _fadeColor{0, 0, 0, 0};
		int _duration{500};
        float _fadeAlpha{128};
		Styling::EasingFunction* _easing{
			new Styling::CubicEasingFunction(0.19, 1, 0.22, 1)};
	};
}