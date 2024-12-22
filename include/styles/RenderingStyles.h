#pragma once
#include "Style.h"
#include "core/Element.h"
#include "core/Macros.h"
#include "core/SkRect.h"
#include "utils/Color.h"

namespace Drift::Styling
{
	class dt_api BackgroundColor : public Style<Color>
	{
	public:
		[[nodiscard]] inline auto StyleName() const -> std::string override
		{
			return "background-color";
		}

		void ApplyEdits(Element* element, Color color) override
		{
			Internals::animateValue(&_color.R, color.R, element);
			Internals::animateValue(&_color.G, color.B, element);
			Internals::animateValue(&_color.B, color.B, element);
			Internals::animateValue(&_color.A, color.A, element);
			Dirty = false;
		}

		inline void BeginDrawStyle(Element* element,
								   SkCanvas* ctx) override
		{
			auto bounds = element->GetBoundingBox();

			SkPaint paint;
			paint.setColor(_color.ToHex());
			paint.setAntiAlias(true);

			ctx->drawRect(SkRect::MakeXYWH(bounds.X + element->GetScrollOffsetX(), bounds.Y + element->GetScrollOffsetY(), bounds.Width, bounds.Height), paint);
		}

	private:
		Color _color;
	};
}