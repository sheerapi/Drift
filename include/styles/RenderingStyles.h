#pragma once
#include "Style.h"
#include "core/Element.h"
#include "core/Logger.h"
#include "core/SkRect.h"
#include "graphics/RendererContext.h"
#include "utils/Color.h"

namespace Drift::Styling
{
	class BackgroundColor : public Style<Color>
	{
	public:
		[[nodiscard]] inline auto StyleName() const -> std::string override
		{
			return "background-color";
		}

		void ApplyEdits(Element* element, Color color) override
		{
			_color = color;
			Dirty = false;
		}

		inline void BeginDrawStyle(Element* element,
								   SkCanvas* ctx) override
		{
			auto bounds = element->GetBoundingBox();

			SkPaint paint;
			paint.setColor(_color.ToHex());
			paint.setAntiAlias(true);

			ctx->drawRect(SkRect::MakeXYWH(bounds.X, bounds.Y, bounds.Width, bounds.Height), paint);
		}

	private:
		Color _color;
	};
}