#include "components/Text.h"
#include "core/SkFont.h"
#include "core/SkFontMetrics.h"
#include "core/SkTextBlob.h"
#include "graphics/RendererContext.h"
#include "styles/TypographyStyles.h"
#include "yoga/YGConfig.h"
#include "yoga/YGNode.h"

namespace Drift
{
	Text::Text(const std::string& content)
	{
		Content = content;
		YGNodeSetContext((YGNodeRef)GetLayoutEngineHandle(), this);
		// YGNodeSetMeasureFunc((YGNodeRef)GetLayoutEngineHandle(), MeasureText);
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

		SkFontMetrics metrics;
		_font.getMetrics(&metrics);

		auto bounds = GetBoundingBox();
		dt_canvas->drawSimpleText(Content.c_str(), Content.size(), SkTextEncoding::kUTF8,
								  bounds.X + GetScrollOffsetX(),
								  bounds.Y + GetScrollOffsetY() - metrics.fAscent, _font, paint);
	}

	auto Text::MeasureText(const YGNode* node, float width, YGMeasureMode widthMode,
					 float height, YGMeasureMode heightMode) -> YGSize
	{
		auto* component = static_cast<Text*>(YGNodeGetContext(node));

		SkString text(component->Content.c_str());

		SkTextBlobBuilder builder;
		SkFontMetrics metrics;
		component->_font.getMetrics(&metrics);

		float lineHeight = metrics.fDescent - metrics.fAscent;
		float totalHeight = 0.0F;
		float maxWidth = 0.0F;

		auto addLine = [&](const char* start, size_t length, float width)
		{
			totalHeight += lineHeight;
			maxWidth = std::max(maxWidth, width);
		};
	}
}