#include "core/FontManager.h"
#include "core/Application.h"
#include "core/Logger.h"
#include "fontconfig/fontconfig.h"
#include "utils/PerformanceTimer.h"

namespace Drift
{
    void FontManager::Init()
    {
        dt_stopwatch();

		if (FcInit() == 0)
        {
            dt_coreFatal("Failed to initialize FontConfig!");
        }

        dt_coreVerbose("Initialized FontConfig {}", FcGetVersion());

        fonts["sans-serif"] = GetFont(ResolveFontStack({}));
	}
}