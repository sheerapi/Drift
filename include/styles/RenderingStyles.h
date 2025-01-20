#pragma once
#include "Style.h"
#include "core/Element.h"
#include "core/Macros.h"
#include "core/SkBlurTypes.h"
#include "core/SkCanvas.h"
#include "core/SkMaskFilter.h"
#include "core/SkRRect.h"
#include "utils/BoundingBoxV.h"
#include "utils/Color.h"
#include "yoga/YGNodeStyle.h"

namespace Drift::Styling
{
	class dt_api BackgroundColor : public Style<Color>
	{
	public:
		[[nodiscard]] inline auto StyleName() const -> std::string override
		{
			return "background-color";
		}

		[[nodiscard]] inline auto StylePriority() const -> int override
		{
			return 7;
		}

		auto GetValue(Element* element) -> Color
		{
			return _color;
		}

		void ApplyEdits(Element* element, Color color) override
		{
			Internals::animateValue(&_color.R, color.R, element);
			Internals::animateValue(&_color.G, color.G, element);
			Internals::animateValue(&_color.B, color.B, element);
			Internals::animateValue(&_color.A, color.A, element);
			Dirty = false;
		}

		inline void BeginDrawStyle(Element* element, SkCanvas* ctx) override
		{
			auto bounds = element->GetBoundingBox();

			SkPaint paint;
			paint.setColor(_color.ToHex());
			paint.setAntiAlias(true);

			ctx->drawRect(SkRect::MakeXYWH(bounds.X + element->GetScrollOffsetX(),
										   bounds.Y + element->GetScrollOffsetY(),
										   bounds.Width, bounds.Height),
						  paint);
		}

	private:
		Color _color;
	};

	class dt_api BorderRadius : public Style<Value, Value, Value, Value>
	{
	public:
		[[nodiscard]] inline auto StyleName() const -> std::string override
		{
			return "border-radius";
		}

		[[nodiscard]] inline auto StylePriority() const -> int override
		{
			return 10;
		}

		void ApplyEdits(Element* element, Value topleft, Value topright, Value bottomleft,
						Value bottomright) override
		{
			if (StyleBase::IsReadyToResolve(element))
			{
				Internals::animateValue(&_topLeftX.Val,
										_topLeftX.Convert(topleft.Unit, element),
										topleft.Val, element);

				Internals::animateValue(&_topRightX.Val,
										_topRightX.Convert(topright.Unit, element),
										topright.Val, element);

				Internals::animateValue(&_bottomLeftX.Val,
										_bottomLeftX.Convert(bottomleft.Unit, element),
										bottomleft.Val, element);

				Internals::animateValue(&_bottomRightX.Val,
										_bottomRightX.Convert(bottomright.Unit, element),
										bottomright.Val, element);
			}
			else
			{
				_topLeftX = topleft;
				_topRightX = topright;
				_bottomRightX = bottomright;
				_bottomLeftX = bottomleft;
			}
			Dirty = false;
		}

		[[nodiscard]] auto GetValue(Element* element) const -> BoundingBoxV
		{
			return {_topRightX, _bottomRightX, _topLeftX, _bottomLeftX};
		}

		void BeginDrawStyle(Element* element, SkCanvas* ctx) override
		{
			ctx->save();

			auto tl = _topLeftX.Resolve(element);
			auto tr = _topRightX.Resolve(element);
			auto bl = _bottomLeftX.Resolve(element);
			auto br = _bottomRightX.Resolve(element);

			SkVector radii[4] = {{tl, tl}, {tr, tr}, {br, br}, {bl, bl}};

			auto bounds = element->GetBoundingBox();
			auto rrect = SkRRect();
			rrect.setRectRadii(SkRect::MakeXYWH(bounds.X + element->GetScrollOffsetX(),
												bounds.Y + element->GetScrollOffsetY(),
												bounds.Width, bounds.Height),
							   radii);

			ctx->clipRRect(rrect, true);
		}

		void EndDrawStyle(Element* element, SkCanvas* ctx) override
		{
			ctx->restore();
		}

	private:
		Value _topLeftX;
		Value _topRightX;
		Value _bottomLeftX;
		Value _bottomRightX;
	};

	class dt_api Border : public Style<Value, Value, Value, Value>
	{
	public:
		[[nodiscard]] inline auto StyleName() const -> std::string override
		{
			return "border";
		}

		[[nodiscard]] inline auto StylePriority() const -> int override
		{
			return 9;
		}

		void ApplyEdits(Element* element, Value top, Value right, Value bottom,
						Value left) override
		{
			if (StyleBase::IsReadyToResolve(element))
			{
				Internals::animateValue(
					&_top.Val,
					_top.Convert(top.Unit, element, PreferredDimension::Height), top.Val,
					element);

				Internals::animateValue(&_right.Val, _right.Convert(right.Unit, element),
										right.Val, element);
				Internals::animateValue(
					&_bottom.Val,
					_bottom.Convert(bottom.Unit, element, PreferredDimension::Height),
					bottom.Val, element);
				Internals::animateValue(&_left.Val, _left.Convert(left.Unit, element),
										left.Val, element);
			}
			else
			{
				_top.Val = top.Val;
				_top.Unit = top.Unit;

				_right.Val = right.Val;
				_right.Unit = right.Unit;

				_bottom.Val = bottom.Val;
				_bottom.Unit = bottom.Unit;

				_left.Val = left.Val;
				_left.Unit = left.Unit;
			}
			Dirty = false;
		}

		[[nodiscard]] auto GetValue(Element* element) const -> BoundingBoxV
		{
			return {_right, _bottom, _left, _top};
		}

		void RecalculateLayout(Element* element) override
		{
			auto resolvedT = _top.Resolve(element, PreferredDimension::Height);
			auto resolvedL = _left.Resolve(element);
			auto resolvedB = _bottom.Resolve(element, PreferredDimension::Height);
			auto resolvedR = _right.Resolve(element);

			if ((resolvedT + resolvedL + resolvedB + resolvedR) == _oldMargin)
			{
				return;
			}

			YGNodeStyleSetBorder((YGNodeRef)element->GetLayoutEngineHandle(), YGEdgeTop,
								 resolvedT);
			YGNodeStyleSetBorder((YGNodeRef)element->GetLayoutEngineHandle(), YGEdgeLeft,
								 resolvedL);
			YGNodeStyleSetBorder((YGNodeRef)element->GetLayoutEngineHandle(),
								 YGEdgeBottom, resolvedB);
			YGNodeStyleSetBorder((YGNodeRef)element->GetLayoutEngineHandle(), YGEdgeRight,
								 resolvedR);
		}

	private:
		Value _top;
		Value _right;
		Value _bottom;
		Value _left;
		float _oldMargin;
	};

	class dt_api BoxShadow : public Style<Value, Value, Value, Color>
	{
	public:
		[[nodiscard]] inline auto StyleName() const -> std::string override
		{
			return "box-shadow";
		}

		[[nodiscard]] inline auto StylePriority() const -> int override
		{
			return 11;
		}

		auto GetValue(Element* element) -> Color
		{
			return _color;
		}

		void ApplyEdits(Element* element, Value xPos, Value yPos, Value radius,
						Color color) override
		{
			Internals::animateValue(&_color.R, color.R, element);
			Internals::animateValue(&_color.G, color.G, element);
			Internals::animateValue(&_color.B, color.B, element);
			Internals::animateValue(&_color.A, color.A, element);

			if (StyleBase::IsReadyToResolve(element))
			{
				Internals::animateValue(&_x.Val, _x.Convert(xPos.Unit, element), xPos.Val,
										element);
				Internals::animateValue(
					&_y.Val, _y.Convert(yPos.Unit, element, PreferredDimension::Height),
					yPos.Val, element);
				Internals::animateValue(&_radius.Val,
										_radius.Convert(radius.Unit, element), radius.Val,
										element);
			}
			else
			{
				_x.Val = xPos.Val;
				_x.Unit = xPos.Unit;

				_y.Val = yPos.Val;
				_y.Unit = yPos.Unit;

				_radius.Val = radius.Val;
				_radius.Unit = radius.Unit;
			}

			Dirty = false;
		}

		inline void BeginDrawStyle(Element* element, SkCanvas* ctx) override
		{
			auto rrect = SkRRect();
			auto bounds = element->GetBoundingBox();

			auto elementRect = SkRect::MakeXYWH(
				bounds.X + element->GetScrollOffsetX() + _x.Resolve(element),
				bounds.Y + element->GetScrollOffsetY() +
					_y.Resolve(element, PreferredDimension::Height),
				bounds.Width, bounds.Height);

			if (element->HasStyle<BorderRadius>())
			{
				auto border = element->GetStyle<BorderRadius>()->GetValue(element);

				auto tl = border.X.Resolve(element);
				auto tr = border.Width.Resolve(element);
				auto bl = border.Y.Resolve(element);
				auto br = border.Height.Resolve(element);

				SkVector radii[4] = {{tl, tl}, {tr, tr}, {br, br}, {bl, bl}};

				rrect.setRectRadii(elementRect, radii);
			}
			else
			{
				SkVector radii[4] = {{0, 0}, {0, 0}, {0, 0}, {0, 0}};
				rrect.setRectRadii(elementRect, radii);
			}

			SkPaint shadowPaint;
			shadowPaint.setColor(SK_ColorBLACK);
			shadowPaint.setMaskFilter(SkMaskFilter::MakeBlur(
				SkBlurStyle::kNormal_SkBlurStyle, _radius.Resolve(element)));
			shadowPaint.setColor(_color.ToHex());
			shadowPaint.setAntiAlias(true);

			ctx->drawRRect(rrect, shadowPaint);
		}

	private:
		Color _color;
		Value _x;
		Value _y;
		Value _radius;
	};
}