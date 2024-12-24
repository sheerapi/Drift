#pragma once
#include "Style.h"
#include "core/Element.h"
#include "core/Macros.h"
#include "core/SkRect.h"
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

	class BorderRadius : public Style<Value, Value, Value, Value>
	{
	public:
		[[nodiscard]] inline auto StyleName() const -> std::string override
		{
			return "border-radius";
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

		void BeginDrawStyle(Element* element, SkCanvas* ctx) override
		{
			
		}

		void EndDrawStyle(Element* element, SkCanvas* ctx) override
		{
		}

	private:
		Value _top;
		Value _right;
		Value _bottom;
		Value _left;
	};

	class Border : public Style<Value, Value, Value, Value>
	{
	public:
		[[nodiscard]] inline auto StyleName() const -> std::string override
		{
			return "border";
		}

		[[nodiscard]] inline auto StylePriority() const -> int override
		{
			return 8;
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
			YGNodeStyleSetBorder((YGNodeRef)element->GetLayoutEngineHandle(),
								   YGEdgeLeft, resolvedL);
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
}