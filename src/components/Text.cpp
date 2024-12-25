#include "components/Text.h"
#include "core/Logger.h"
#include "styles/TypographyStyles.h"

namespace Drift
{
    void Text::Draw()
    {
        float size = GetStyle<Styling::FontSize>()->GetValue(this);
        auto fonts = GetStyle<Styling::FontFamily>()->GetValue(this);

        dt_info("Drawing {} at {}px with font {}", Content, size, fonts[0]);
    }
}