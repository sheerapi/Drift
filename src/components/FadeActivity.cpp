#include "components/FadeActivity.h"
#include "graphics/RendererContext.h"
#include "styles/AnimationScheduler.h"
#include "core/Scheduler.h"

namespace Drift::Components
{
    void FadeActivity::BeginDraw()
    {
        dt_canvas->saveLayerAlphaf(nullptr, _fadeColor.A / 255);
        dt_canvas->clear(Color(_fadeColor.R, _fadeColor.G, _fadeColor.B, _fadeAlpha).ToHex());
    }

    void FadeActivity::EndDraw()
    {
        dt_canvas->restore();
    }

    void FadeActivity::OnResume()
    {
        Styling::AnimationScheduler::AnimateValue(&_fadeColor.A, 255, _duration, _easing);
    }

    void FadeActivity::OnDestroy()
    {
		Styling::AnimationScheduler::AnimateValue(&_fadeColor.A, 0, _duration, _easing);
        dt_setTimeout([this](){
            Finish();
        }, _duration);
	}
}