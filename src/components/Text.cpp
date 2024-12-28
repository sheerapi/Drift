#include "components/Text.h"
#include "core/SkFont.h"
#include "core/SkFontMetrics.h"
#include "core/SkTextBlob.h"
#include "graphics/RendererContext.h"
#include "styles/LayoutStyles.h"
#include "styles/TypographyStyles.h"
#include "yoga/YGConfig.h"
#include "yoga/YGNode.h"
#include <cfloat>

namespace Drift
{
	Text::Text(const std::string& content)
	{
		Content = content;
		YGNodeSetContext((YGNodeRef)GetLayoutEngineHandle(), this);
		// YGNodeSetMeasureFunc((YGNodeRef)GetLayoutEngineHandle(), MeasureText);
		YGNodeSetBaselineFunc((YGNodeRef)GetLayoutEngineHandle(), BaselineText);
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
								  bounds.Y + GetScrollOffsetY() +
									  GetStyle<Styling::FontSize>()->GetValue(this),
								  _font, paint);
	}

	auto Text::MeasureText(const YGNode* node, float width, YGMeasureMode widthMode,
						   float height, YGMeasureMode heightMode) -> YGSize
	{
		auto* component = static_cast<Text*>(YGNodeGetContext(node));

		SkString text(component->Content.c_str());

		SkTextBlobBuilder builder;
		SkFontMetrics metrics;
		component->_font.getMetrics(&metrics);

		float lineHeight = component->_font.getSize() * 1.125F;
		float letterSpacing = 0;

		if (component->HasStyle<Styling::LineHeight>() &&
			component->GetStyle<Styling::LineHeight>()->GetValue(component) != -1)
		{
			lineHeight = component->_font.getSize() *
						 component->GetStyle<Styling::LineHeight>()->GetValue(component);
		}

		if (component->HasStyle<Styling::LetterSpacing>())
		{
			letterSpacing =
				component->GetStyle<Styling::LetterSpacing>()->GetValue(component);
		}

		float maxWidth = (widthMode == YGMeasureModeUndefined)
							 ? std::numeric_limits<float>::infinity()
							 : width;

		float cursorX = 0.F;
		float cursorY = 0.F;
		float lineWidth = 0.F;

		for (size_t i = 0; component->Content.size() < text.size();)
		{
			
		}

		return YGSize{
			0, 0
		};
	}

	auto Text::BaselineText(const YGNode* node, float width, float height) -> float
	{
		auto* component = static_cast<Text*>(YGNodeGetContext(node));

		SkFontMetrics metrics;
		component->_font.getMetrics(&metrics);

		float baseline = -metrics.fAscent;
		Align alignment = Align::FlexStart;

		if (component->HasStyle<Styling::AlignItems>())
		{
			alignment = component->GetStyle<Styling::AlignItems>()->GetValue(component);
		}

		if (alignment == Align::Center)
		{
			baseline = height / 2.0F - (metrics.fAscent + metrics.fDescent) / 2.0F;
		}
		else if (alignment == Align::FlexEnd)
		{
			baseline = height + metrics.fDescent;
		}

		return baseline;
	}
}