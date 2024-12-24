#pragma once
#include "core/Element.h"
#include "core/LayoutEnums.h"
#include "styles/Style.h"
#include "utils/BoundingBoxV.h"
#include "utils/Vector2.h"
#include "yoga/YGNodeStyle.h"

namespace Drift::Styling
{
	class Width : public Style<Value>
	{
	public:
		[[nodiscard]] inline auto StyleName() const -> std::string override
		{
			return "width";
		}

		[[nodiscard]] inline auto StylePriority() const -> int override
		{
			return 10;
		}

		void ApplyEdits(Element* element, Value val) override
		{
			if (StyleBase::IsReadyToResolve(element))
			{
				Internals::animateValue(&_width.Val, _width.Convert(val.Unit, element),
										val.Val, element);
			}
			else
			{
				_width.Val = val.Val;
				_width.Unit = val.Unit;
			}
			Dirty = false;
		}

		[[nodiscard]] auto GetValue() const -> float
		{
			return _width.Val;
		}

		void RecalculateLayout(Element* element) override
		{
			auto resolved = _width.Resolve(element);

			if (resolved == _oldWidth)
			{
				return;
			}

			YGNodeStyleSetWidth((YGNodeRef)element->GetLayoutEngineHandle(), resolved);
			_oldWidth = resolved;
		}

	private:
		Value _width;
		float _oldWidth;
	};

	// no i will not bother to change the names
	// there are too much properties i have to replace leave me alone
	class Height : public Style<Value>
	{
	public:
		[[nodiscard]] inline auto StyleName() const -> std::string override
		{
			return "height";
		}

		[[nodiscard]] inline auto StylePriority() const -> int override
		{
			return 10;
		}

		void ApplyEdits(Element* element, Value val) override
		{
			if (StyleBase::IsReadyToResolve(element))
			{
				Internals::animateValue(
					&_width.Val,
					_width.Convert(val.Unit, element, PreferredDimension::Height),
					val.Val, element);
			}
			else
			{
				_width.Val = val.Val;
				_width.Unit = val.Unit;
			}
			Dirty = false;
		}

		[[nodiscard]] auto GetValue() const -> float
		{
			return _width.Val;
		}

		void RecalculateLayout(Element* element) override
		{
			auto resolved = _width.Resolve(element, PreferredDimension::Height);

			if (resolved == _oldWidth)
			{
				return;
			}

			YGNodeStyleSetHeight((YGNodeRef)element->GetLayoutEngineHandle(), resolved);
			_oldWidth = resolved;
		}

	private:
		Value _width;
		float _oldWidth;
	};

	class MaxWidth : public Style<Value>
	{
	public:
		[[nodiscard]] inline auto StyleName() const -> std::string override
		{
			return "max-width";
		}

		[[nodiscard]] inline auto StylePriority() const -> int override
		{
			return 10;
		}

		void ApplyEdits(Element* element, Value val) override
		{
			if (StyleBase::IsReadyToResolve(element))
			{
				Internals::animateValue(&_width.Val, _width.Convert(val.Unit, element),
										val.Val, element);
			}
			else
			{
				_width.Val = val.Val;
				_width.Unit = val.Unit;
			}
			Dirty = false;
		}

		[[nodiscard]] auto GetValue() const -> float
		{
			return _width.Val;
		}

		void RecalculateLayout(Element* element) override
		{
			auto resolved = _width.Resolve(element);

			if (resolved == _oldWidth)
			{
				return;
			}
			YGNodeStyleSetMaxWidth((YGNodeRef)element->GetLayoutEngineHandle(), resolved);
			_oldWidth = resolved;
		}

	private:
		Value _width;
		float _oldWidth;
	};

	class MaxHeight : public Style<Value>
	{
	public:
		[[nodiscard]] inline auto StyleName() const -> std::string override
		{
			return "max-height";
		}

		[[nodiscard]] inline auto StylePriority() const -> int override
		{
			return 10;
		}

		void ApplyEdits(Element* element, Value val) override
		{
			if (StyleBase::IsReadyToResolve(element))
			{
				Internals::animateValue(
					&_width.Val,
					_width.Convert(val.Unit, element, PreferredDimension::Height),
					val.Val, element);
			}
			else
			{
				_width.Val = val.Val;
				_width.Unit = val.Unit;
			}
			Dirty = false;
		}

		[[nodiscard]] auto GetValue() const -> float
		{
			return _width.Val;
		}

		void RecalculateLayout(Element* element) override
		{
			auto resolved = _width.Resolve(element, PreferredDimension::Height);

			if (resolved == _oldWidth)
			{
				return;
			}
			YGNodeStyleSetMaxHeight((YGNodeRef)element->GetLayoutEngineHandle(),
									resolved);
			_oldWidth = resolved;
		}

	private:
		Value _width;
		float _oldWidth;
	};

	class MinWidth : public Style<Value>
	{
	public:
		[[nodiscard]] inline auto StyleName() const -> std::string override
		{
			return "min-width";
		}

		[[nodiscard]] inline auto StylePriority() const -> int override
		{
			return 10;
		}

		void ApplyEdits(Element* element, Value val) override
		{
			if (StyleBase::IsReadyToResolve(element))
			{
				Internals::animateValue(&_width.Val, _width.Convert(val.Unit, element),
										val.Val, element);
			}
			else
			{
				_width.Val = val.Val;
				_width.Unit = val.Unit;
			}
			Dirty = false;
		}

		[[nodiscard]] auto GetValue() const -> float
		{
			return _width.Val;
		}

		void RecalculateLayout(Element* element) override
		{
			auto resolved = _width.Resolve(element);

			if (resolved == _oldWidth)
			{
				return;
			}
			YGNodeStyleSetMinWidth((YGNodeRef)element->GetLayoutEngineHandle(), resolved);
			_oldWidth = resolved;
		}

	private:
		Value _width;
		float _oldWidth;
	};

	class MinHeight : public Style<Value>
	{
	public:
		[[nodiscard]] inline auto StyleName() const -> std::string override
		{
			return "min-height";
		}

		[[nodiscard]] inline auto StylePriority() const -> int override
		{
			return 10;
		}

		void ApplyEdits(Element* element, Value val) override
		{
			if (StyleBase::IsReadyToResolve(element))
			{
				Internals::animateValue(
					&_width.Val,
					_width.Convert(val.Unit, element, PreferredDimension::Height),
					val.Val, element);
			}
			else
			{
				_width.Val = val.Val;
				_width.Unit = val.Unit;
			}
			Dirty = false;
		}

		[[nodiscard]] auto GetValue() const -> float
		{
			return _width.Val;
		}

		void RecalculateLayout(Element* element) override
		{
			auto resolved = _width.Resolve(element, PreferredDimension::Height);

			if (resolved == _oldWidth)
			{
				return;
			}
			YGNodeStyleSetMinHeight((YGNodeRef)element->GetLayoutEngineHandle(),
									resolved);
			_oldWidth = resolved;
		}

	private:
		Value _width;
		float _oldWidth;
	};

	class FlexBasis : public Style<Value>
	{
	public:
		[[nodiscard]] inline auto StyleName() const -> std::string override
		{
			return "flex-basis";
		}

		[[nodiscard]] inline auto StylePriority() const -> int override
		{
			return 10;
		}

		void ApplyEdits(Element* element, Value val) override
		{
			if (StyleBase::IsReadyToResolve(element))
			{
				auto dimension = PreferredDimension::Width;

				if (!element->IsOrphan())
				{
					dimension =
						(element->GetParent()->FlexDirection() == Direction::Row ||
						 element->GetParent()->FlexDirection() == Direction::RowReverse)
							? PreferredDimension::Width
							: PreferredDimension::Height;
				}

				Internals::animateValue(&_width.Val,
										_width.Convert(val.Unit, element, dimension),
										val.Val, element);
			}
			else
			{
				_width.Val = val.Val;
				_width.Unit = val.Unit;
			}
			Dirty = false;
		}

		[[nodiscard]] auto GetValue() const -> float
		{
			return _width.Val;
		}

		void RecalculateLayout(Element* element) override
		{
			auto dimension = PreferredDimension::Width;

			if (!element->IsOrphan())
			{
				dimension =
					(element->GetParent()->FlexDirection() == Direction::Row ||
					 element->GetParent()->FlexDirection() == Direction::RowReverse)
						? PreferredDimension::Width
						: PreferredDimension::Height;
			}

			auto resolved = _width.Resolve(element, dimension);

			if (resolved == _oldWidth)
			{
				return;
			}

			YGNodeStyleSetFlexBasis((YGNodeRef)element->GetLayoutEngineHandle(),
									resolved);
			_oldWidth = resolved;
		}

	private:
		Value _width;
		float _oldWidth;
	};

	class Gap : public Style<Value, Value>
	{
	public:
		[[nodiscard]] inline auto StyleName() const -> std::string override
		{
			return "gap";
		}

		[[nodiscard]] inline auto StylePriority() const -> int override
		{
			return 10;
		}

		void ApplyEdits(Element* element, Value val, Value val2) override
		{
			if (StyleBase::IsReadyToResolve(element))
			{
				Internals::animateValue(&_gapHorizontal.Val,
										_gapHorizontal.Convert(val.Unit, element),
										val.Val, element);
				Internals::animateValue(
					&_gapVertical.Val,
					_gapVertical.Convert(val.Unit, element, PreferredDimension::Height),
					val2.Val, element);
			}
			else
			{
				_gapHorizontal.Val = val.Val;
				_gapHorizontal.Unit = val.Unit;

				_gapVertical.Val = val2.Val;
				_gapVertical.Unit = val2.Unit;
			}
			Dirty = false;
		}

		[[nodiscard]] auto GetValue() const -> Vector2
		{
			return {_gapHorizontal.Val, _gapVertical.Val};
		}

		void RecalculateLayout(Element* element) override
		{
			auto gapH = _gapHorizontal.Resolve(element, PreferredDimension::Width);
			auto gapV = _gapVertical.Resolve(element, PreferredDimension::Height);

			if ((gapH + gapV) == _oldGap)
			{
				return;
			}

			YGNodeStyleSetGap((YGNodeRef)element->GetLayoutEngineHandle(), YGGutterColumn,
							  gapH);
			YGNodeStyleSetGap((YGNodeRef)element->GetLayoutEngineHandle(), YGGutterRow,
							  gapV);

			_oldGap = gapH + gapV;
		}

	private:
		Value _gapHorizontal;
		Value _gapVertical;
		float _oldGap;
	};

	class FlexGrow : public Style<float>
	{
	public:
		[[nodiscard]] inline auto StyleName() const -> std::string override
		{
			return "flex-grow";
		}

		[[nodiscard]] inline auto StylePriority() const -> int override
		{
			return 10;
		}

		void ApplyEdits(Element* element, float val) override
		{
			Internals::animateValue(&_width, val, element);
			Dirty = false;
		}

		[[nodiscard]] auto GetValue() const -> float
		{
			return _width;
		}

		void RecalculateLayout(Element* element) override
		{
			if (_width == _oldWidth)
			{
				return;
			}

			YGNodeStyleSetFlexGrow((YGNodeRef)element->GetLayoutEngineHandle(), _width);
			_oldWidth = _width;
		}

	private:
		float _width;
		float _oldWidth;
	};

	class FlexShrink : public Style<float>
	{
	public:
		[[nodiscard]] inline auto StyleName() const -> std::string override
		{
			return "flex-shrink";
		}

		[[nodiscard]] inline auto StylePriority() const -> int override
		{
			return 10;
		}

		void ApplyEdits(Element* element, float val) override
		{
			Internals::animateValue(&_width, val, element);
			Dirty = false;
		}

		[[nodiscard]] auto GetValue() const -> float
		{
			return _width;
		}

		void RecalculateLayout(Element* element) override
		{
			if (_width == _oldWidth)
			{
				return;
			}

			YGNodeStyleSetFlexShrink((YGNodeRef)element->GetLayoutEngineHandle(), _width);
			_oldWidth = _width;
		}

	private:
		float _width;
		float _oldWidth;
	};

	class AspectRatio : public Style<float>
	{
	public:
		[[nodiscard]] inline auto StyleName() const -> std::string override
		{
			return "aspect-ratio";
		}

		[[nodiscard]] inline auto StylePriority() const -> int override
		{
			return 10;
		}

		void ApplyEdits(Element* element, float val) override
		{
			Internals::animateValue(&_width, val, element);
			Dirty = false;
		}

		[[nodiscard]] auto GetValue() const -> float
		{
			return _width;
		}

		void RecalculateLayout(Element* element) override
		{
			if (_width == _oldWidth)
			{
				return;
			}

			YGNodeStyleSetAspectRatio((YGNodeRef)element->GetLayoutEngineHandle(),
									  _width);
			_oldWidth = _width;
		}

	private:
		float _width;
		float _oldWidth;
	};

	class Margin : public Style<Value, Value, Value, Value>
	{
	public:
		[[nodiscard]] inline auto StyleName() const -> std::string override
		{
			return "margin";
		}

		[[nodiscard]] inline auto StylePriority() const -> int override
		{
			return 10;
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

		[[nodiscard]] auto GetValue() const -> BoundingBoxV
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

			YGNodeStyleSetMargin((YGNodeRef)element->GetLayoutEngineHandle(), YGEdgeTop,
								 resolvedT);
			YGNodeStyleSetMargin((YGNodeRef)element->GetLayoutEngineHandle(), YGEdgeLeft,
								 resolvedL);
			YGNodeStyleSetMargin((YGNodeRef)element->GetLayoutEngineHandle(),
								 YGEdgeBottom, resolvedB);
			YGNodeStyleSetMargin((YGNodeRef)element->GetLayoutEngineHandle(), YGEdgeRight,
								 resolvedR);
		}

	private:
		Value _top;
		Value _right;
		Value _bottom;
		Value _left;
		float _oldMargin;
	};

	class Padding : public Style<Value, Value, Value, Value>
	{
	public:
		[[nodiscard]] inline auto StyleName() const -> std::string override
		{
			return "padding";
		}

		[[nodiscard]] inline auto StylePriority() const -> int override
		{
			return 10;
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

		[[nodiscard]] auto GetValue() const -> BoundingBoxV
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

			YGNodeStyleSetPadding((YGNodeRef)element->GetLayoutEngineHandle(), YGEdgeTop,
								  resolvedT);
			YGNodeStyleSetPadding((YGNodeRef)element->GetLayoutEngineHandle(), YGEdgeLeft,
								  resolvedL);
			YGNodeStyleSetPadding((YGNodeRef)element->GetLayoutEngineHandle(),
								  YGEdgeBottom, resolvedB);
			YGNodeStyleSetPadding((YGNodeRef)element->GetLayoutEngineHandle(),
								  YGEdgeRight, resolvedR);
		}

	private:
		Value _top;
		Value _right;
		Value _bottom;
		Value _left;
		float _oldMargin;
	};

	class Position : public Style<Value, Value, Value, Value>
	{
	public:
		[[nodiscard]] inline auto StyleName() const -> std::string override
		{
			return "position";
		}

		[[nodiscard]] inline auto StylePriority() const -> int override
		{
			return 10;
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

		[[nodiscard]] auto GetValue() const -> BoundingBoxV
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

			YGNodeStyleSetPosition((YGNodeRef)element->GetLayoutEngineHandle(), YGEdgeTop,
								   resolvedT);
			YGNodeStyleSetPosition((YGNodeRef)element->GetLayoutEngineHandle(),
								   YGEdgeLeft, resolvedL);
			YGNodeStyleSetPosition((YGNodeRef)element->GetLayoutEngineHandle(),
								   YGEdgeBottom, resolvedB);
			YGNodeStyleSetPosition((YGNodeRef)element->GetLayoutEngineHandle(),
								   YGEdgeRight, resolvedR);
		}

	private:
		Value _top;
		Value _right;
		Value _bottom;
		Value _left;
		float _oldMargin;
	};

	class AlignContent : public Style<Drift::Align>
	{
	public:
		[[nodiscard]] inline auto StyleName() const -> std::string override
		{
			return "align-content";
		}

		[[nodiscard]] inline auto StylePriority() const -> int override
		{
			return 10;
		}

		[[nodiscard]] inline auto IsAnimatable() const -> bool override
		{
			return false;
		}

		void ApplyEdits(Element* element, Drift::Align val) override
		{
			_val = val;
			Dirty = false;
		}

		[[nodiscard]] auto GetValue() const -> Drift::Align
		{
			return _val;
		}

		void RecalculateLayout(Element* element) override
		{
			if (_val == _oldVal)
			{
				return;
			}

			YGNodeStyleSetAlignContent((YGNodeRef)element->GetLayoutEngineHandle(),
									   (YGAlign)_val);
			_oldVal = _val;
		}

	private:
		Drift::Align _val;
		Drift::Align _oldVal;
	};

	class AlignItems : public Style<Drift::Align>
	{
	public:
		[[nodiscard]] inline auto StyleName() const -> std::string override
		{
			return "align-items";
		}

		[[nodiscard]] inline auto StylePriority() const -> int override
		{
			return 10;
		}

		[[nodiscard]] inline auto IsAnimatable() const -> bool override
		{
			return false;
		}

		void ApplyEdits(Element* element, Drift::Align val) override
		{
			_val = val;
			Dirty = false;
		}

		[[nodiscard]] auto GetValue() const -> Drift::Align
		{
			return _val;
		}

		void RecalculateLayout(Element* element) override
		{
			if (_val == _oldVal)
			{
				return;
			}

			YGNodeStyleSetAlignItems((YGNodeRef)element->GetLayoutEngineHandle(),
									 (YGAlign)_val);
			_oldVal = _val;
		}

	private:
		Drift::Align _val;
		Drift::Align _oldVal;
	};

	class JustifyContent : public Style<Drift::Justify>
	{
	public:
		[[nodiscard]] inline auto StyleName() const -> std::string override
		{
			return "justify-content";
		}

		[[nodiscard]] inline auto StylePriority() const -> int override
		{
			return 10;
		}

		[[nodiscard]] inline auto IsAnimatable() const -> bool override
		{
			return false;
		}

		void ApplyEdits(Element* element, Drift::Justify val) override
		{
			_val = val;
			Dirty = false;
		}

		[[nodiscard]] auto GetValue() const -> Drift::Justify
		{
			return _val;
		}

		void RecalculateLayout(Element* element) override
		{
			if (_val == _oldVal)
			{
				return;
			}

			YGNodeStyleSetJustifyContent((YGNodeRef)element->GetLayoutEngineHandle(),
										 (YGJustify)_val);
			_oldVal = _val;
		}

	private:
		Drift::Justify _val;
		Drift::Justify _oldVal;
	};

	class Display : public Style<Drift::DisplayType>
	{
	public:
		[[nodiscard]] inline auto StyleName() const -> std::string override
		{
			return "display";
		}

		[[nodiscard]] inline auto StylePriority() const -> int override
		{
			return 10;
		}

		[[nodiscard]] inline auto IsAnimatable() const -> bool override
		{
			return false;
		}

		void ApplyEdits(Element* element, Drift::DisplayType val) override
		{
			_val = val;
			Dirty = false;
		}

		[[nodiscard]] auto GetValue() const -> Drift::DisplayType
		{
			return _val;
		}

		void RecalculateLayout(Element* element) override
		{
			if (_val == _oldVal)
			{
				return;
			}

			YGNodeStyleSetDisplay((YGNodeRef)element->GetLayoutEngineHandle(),
								  (YGDisplay)_val);
			_oldVal = _val;
		}

	private:
		Drift::DisplayType _val;
		Drift::DisplayType _oldVal;
	};

	class Overflow : public Style<Drift::OverflowType>
	{
	public:
		[[nodiscard]] inline auto StyleName() const -> std::string override
		{
			return "overflow";
		}

		[[nodiscard]] inline auto StylePriority() const -> int override
		{
			return 10;
		}

		[[nodiscard]] inline auto IsAnimatable() const -> bool override
		{
			return false;
		}

		void ApplyEdits(Element* element, Drift::OverflowType val) override
		{
			_val = val;
			Dirty = false;
		}

		[[nodiscard]] auto GetValue() const -> Drift::OverflowType
		{
			return _val;
		}

		void RecalculateLayout(Element* element) override
		{
			if (_val == _oldVal)
			{
				return;
			}

			YGNodeStyleSetOverflow((YGNodeRef)element->GetLayoutEngineHandle(),
								   (YGOverflow)_val);
			_oldVal = _val;
		}

	private:
		Drift::OverflowType _val;
		Drift::OverflowType _oldVal;
	};

	class FlexWrap : public Style<Drift::WrapType>
	{
	public:
		[[nodiscard]] inline auto StyleName() const -> std::string override
		{
			return "flex-wrap";
		}

		[[nodiscard]] inline auto StylePriority() const -> int override
		{
			return 10;
		}

		[[nodiscard]] inline auto IsAnimatable() const -> bool override
		{
			return false;
		}

		void ApplyEdits(Element* element, Drift::WrapType val) override
		{
			_val = val;
			Dirty = false;
		}

		[[nodiscard]] auto GetValue() const -> Drift::WrapType
		{
			return _val;
		}

		void RecalculateLayout(Element* element) override
		{
			if (_val == _oldVal)
			{
				return;
			}

			YGNodeStyleSetFlexWrap((YGNodeRef)element->GetLayoutEngineHandle(),
								   (YGWrap)_val);
			_oldVal = _val;
		}

	private:
		Drift::WrapType _val;
		Drift::WrapType _oldVal;
	};

	class FlexDirection : public Style<Drift::Direction>
	{
	public:
		[[nodiscard]] inline auto StyleName() const -> std::string override
		{
			return "flex-direction";
		}

		[[nodiscard]] inline auto StylePriority() const -> int override
		{
			return 10;
		}

		[[nodiscard]] inline auto IsAnimatable() const -> bool override
		{
			return false;
		}

		void ApplyEdits(Element* element, Drift::Direction val) override
		{
			_val = val;
			Dirty = false;
		}

		[[nodiscard]] auto GetValue() const -> Drift::Direction
		{
			return _val;
		}

		void RecalculateLayout(Element* element) override
		{
			if (_val == _oldVal)
			{
				return;
			}

			YGNodeStyleSetFlexDirection((YGNodeRef)element->GetLayoutEngineHandle(),
										(YGFlexDirection)_val);
			_oldVal = _val;
		}

	private:
		Drift::Direction _val;
		Drift::Direction _oldVal;
	};

	class PositionType : public Style<Drift::PositionType>
	{
	public:
		[[nodiscard]] inline auto StyleName() const -> std::string override
		{
			return "position-type";
		}

		[[nodiscard]] inline auto StylePriority() const -> int override
		{
			return 10;
		}

		[[nodiscard]] inline auto IsAnimatable() const -> bool override
		{
			return false;
		}

		void ApplyEdits(Element* element, Drift::PositionType val) override
		{
			_val = val;
			Dirty = false;
		}

		[[nodiscard]] auto GetValue() const -> Drift::PositionType
		{
			return _val;
		}

		void RecalculateLayout(Element* element) override
		{
			if (_val == _oldVal)
			{
				return;
			}

			YGNodeStyleSetPositionType((YGNodeRef)element->GetLayoutEngineHandle(),
									   (YGPositionType)_val);
			_oldVal = _val;
		}

	private:
		Drift::PositionType _val;
		Drift::PositionType _oldVal;
	};

	class BoxSizing : public Style<Drift::BoxSizingType>
	{
	public:
		[[nodiscard]] inline auto StyleName() const -> std::string override
		{
			return "box-sizing";
		}

		[[nodiscard]] inline auto StylePriority() const -> int override
		{
			return 10;
		}

		[[nodiscard]] inline auto IsAnimatable() const -> bool override
		{
			return false;
		}

		void ApplyEdits(Element* element, Drift::BoxSizingType val) override
		{
			_val = val;
			Dirty = false;
		}

		[[nodiscard]] auto GetValue() const -> Drift::BoxSizingType
		{
			return _val;
		}

		void RecalculateLayout(Element* element) override
		{
			if (_val == _oldVal)
			{
				return;
			}

			YGNodeStyleSetBoxSizing((YGNodeRef)element->GetLayoutEngineHandle(),
									(YGBoxSizing)_val);
			_oldVal = _val;
		}

	private:
		Drift::BoxSizingType _val;
		Drift::BoxSizingType _oldVal;
	};
}