#include "components/Text.h"
#include "core/Logger.h"
#include "graphics/RendererContext.h"
#include "styles/TypographyStyles.h"

namespace Drift
{
	void Text::Draw()
	{
		float size = GetStyle<Styling::FontSize>()->GetValue(this);
		auto* font = GetStyle<Styling::FontFamily>()->GetValue(this);

		dt_canvas->drawSimpleText()
	}
}