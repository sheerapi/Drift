#include "components/activities/ActivityEffect.h"
#include "core/Activity.h"
#include "graphics/RendererContext.h"
#include "styles/AnimationScheduler.h"

namespace Drift::Components::Activities
{
	void FadeEffect::Present(Activity* activity)
	{
		Styling::AnimationScheduler::AnimateValue(
			&_color.A, 255, activity->GetEasingDuration(), activity->GetEasing());
	}

	void FadeEffect::Shutdown(Activity* activity)
	{
		Styling::AnimationScheduler::AnimateValue(
			&_color.A, 0, activity->GetEasingDuration(), activity->GetEasing());
	}

	void FadeEffect::BeginDraw()
	{
		dt_canvas->saveLayerAlphaf(nullptr, _color.A / 255);
		dt_canvas->clear(Color(_color.R, _color.G, _color.B, _alpha * 255).ToHex());
	}

	void FadeEffect::EndDraw()
	{
		dt_canvas->restore();
	}
}