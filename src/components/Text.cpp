#include "components/Text.h"
#include "core/SkFontTypes.h"
#include "graphics/RendererContext.h"
#include "styles/TypographyStyles.h"

namespace Drift
{
	Text::Text(const std::string& content)
	{
		Content = content;
	}

	void Text::Update()
	{
		_font.setTypeface(GetStyle<Styling::FontFamily>()->GetValue(this));
		_font.setSize(GetStyle<Styling::FontSize>()->GetValue(this));
	}

	void Text::Draw()
	{
		SkPaint paint;
		paint.setColor(SK_ColorBLACK);
		paint.setAntiAlias(true);

		auto bounds = GetBoundingBox();
		dt_canvas->drawSimpleText(Content.c_str(), Content.size(), SkTextEncoding::kUTF8,
								  bounds.X + GetScrollOffsetX(),
								  bounds.Y + GetScrollOffsetY(), _font, paint);
	}
}