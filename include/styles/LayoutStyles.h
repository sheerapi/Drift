#pragma once
#include "core/Element.h"
#include "core/LayoutEnums.h"
#include "styles/Style.h"
#include "utils/BoundingBoxV.h"
#include "utils/Vector2.h"
#include "yoga/YGNodeStyle.h"

namespace Drift::Styling
{
	class dt_api Width : public Style<Value>
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

		[[nodiscard]] auto GetValue(Element* element) const -> float
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

			if (_width.Unit == UnitType::Percent)
			{
				YGNodeStyleSetWidthPercent((YGNodeRef)element->GetLayoutEngineHandle(), _width.Val);
				_oldWidth = resolved;
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
	class dt_api Height : public Style<Value>
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

		[[nodiscard]] auto GetValue(Element* element) const -> float
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

			if (_width.Unit == UnitType::Percent)
			{
				YGNodeStyleSetHeightPercent((YGNodeRef)element->GetLayoutEngineHandle(),
										   _width.Val);
				_oldWidth = resolved;
				return;
			}

			YGNodeStyleSetHeight((YGNodeRef)element->GetLayoutEngineHandle(), resolved);
			_oldWidth = resolved;
		}

	private:
		Value _width;
		float _oldWidth;
	};

	class dt_api MaxWidth : public Style<Value>
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

		[[nodiscard]] auto GetValue(Element* element) const -> float
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

			if (_width.Unit == UnitType::Percent)
			{
				YGNodeStyleSetMaxWidthPercent((YGNodeRef)element->GetLayoutEngineHandle(),
										   _width.Val);
				_oldWidth = resolved;
				return;
			}

			YGNodeStyleSetMaxWidth((YGNodeRef)element->GetLayoutEngineHandle(), resolved);
			_oldWidth = resolved;
		}

	private:
		Value _width;
		float _oldWidth;
	};

	class dt_api MaxHeight : public Style<Value>
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

		[[nodiscard]] auto GetValue(Element* element) const -> float
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

			if (_width.Unit == UnitType::Percent)
			{
				YGNodeStyleSetMaxHeightPercent((YGNodeRef)element->GetLayoutEngineHandle(),
										   _width.Val);
				_oldWidth = resolved;
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

	class dt_api MinWidth : public Style<Value>
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

		[[nodiscard]] auto GetValue(Element* element) const -> float
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

			if (_width.Unit == UnitType::Percent)
			{
				YGNodeStyleSetMinWidthPercent((YGNodeRef)element->GetLayoutEngineHandle(),
										   _width.Val);
				_oldWidth = resolved;
				return;
			}

			YGNodeStyleSetMinWidth((YGNodeRef)element->GetLayoutEngineHandle(), resolved);
			_oldWidth = resolved;
		}

	private:
		Value _width;
		float _oldWidth;
	};

	class dt_api MinHeight : public Style<Value>
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

		[[nodiscard]] auto GetValue(Element* element) const -> float
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

			if (_width.Unit == UnitType::Percent)
			{
				YGNodeStyleSetMinHeightPercent((YGNodeRef)element->GetLayoutEngineHandle(), _width.Val);
				_oldWidth = resolved;
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

	class dt_api FlexBasis : public Style<Value>
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

		[[nodiscard]] auto GetValue(Element* element) const -> float
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

			if (_width.Unit == UnitType::Percent)
			{
				YGNodeStyleSetFlexBasisPercent((YGNodeRef)element->GetLayoutEngineHandle(),
										   _width.Val);
				_oldWidth = resolved;
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

	class dt_api Gap : public Style<Value, Value>
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

		[[nodiscard]] auto GetValue(Element* element) const -> Vector2
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

			if (_gapHorizontal.Unit == UnitType::Percent)
			{
				YGNodeStyleSetGapPercent((YGNodeRef)element->GetLayoutEngineHandle(),
										 YGGutterColumn, gapH);
			}
			else
			{
				YGNodeStyleSetGap((YGNodeRef)element->GetLayoutEngineHandle(),
								  YGGutterColumn, gapH);
			}

			if (_gapVertical.Unit == UnitType::Percent)
			{
				YGNodeStyleSetGapPercent((YGNodeRef)element->GetLayoutEngineHandle(),
										 YGGutterRow, gapH);
			}
			else
			{
				YGNodeStyleSetGap((YGNodeRef)element->GetLayoutEngineHandle(),
								  YGGutterRow, gapV);
			}

			_oldGap = gapH + gapV;
		}

	private:
		Value _gapHorizontal;
		Value _gapVertical;
		float _oldGap;
	};

	class dt_api FlexGrow : public Style<float>
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

		[[nodiscard]] auto GetValue(Element* element) const -> float
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

	class dt_api FlexShrink : public Style<float>
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

		[[nodiscard]] auto GetValue(Element* element) const -> float
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

	class dt_api AspectRatio : public Style<float>
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

		[[nodiscard]] auto GetValue(Element* element) const -> float
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

	class dt_api Margin : public Style<Value, Value, Value, Value>
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

			if (_top.Unit == UnitType::Percent)
			{
				YGNodeStyleSetMarginPercent((YGNodeRef)element->GetLayoutEngineHandle(),
											YGEdgeTop, _top.Val);
			}
			else
			{
				YGNodeStyleSetMargin((YGNodeRef)element->GetLayoutEngineHandle(),
									 YGEdgeTop, resolvedT);
			}

			if (_bottom.Unit == UnitType::Percent)
			{
				YGNodeStyleSetMarginPercent((YGNodeRef)element->GetLayoutEngineHandle(),
											YGEdgeBottom, _bottom.Val);
			}
			else
			{
				YGNodeStyleSetMargin((YGNodeRef)element->GetLayoutEngineHandle(),
									 YGEdgeBottom, resolvedB);
			}

			if (_right.Unit == UnitType::Percent)
			{
				YGNodeStyleSetMarginPercent((YGNodeRef)element->GetLayoutEngineHandle(),
											YGEdgeRight, _right.Val);
			}
			else
			{
				YGNodeStyleSetMargin((YGNodeRef)element->GetLayoutEngineHandle(),
									 YGEdgeRight, resolvedR);
			}

			if (_left.Unit == UnitType::Percent)
			{
				YGNodeStyleSetMarginPercent((YGNodeRef)element->GetLayoutEngineHandle(),
											YGEdgeLeft, _left.Val);
			}
			else
			{
				YGNodeStyleSetMargin((YGNodeRef)element->GetLayoutEngineHandle(),
									 YGEdgeLeft, resolvedL);
			}

			_oldMargin = resolvedT + resolvedL + resolvedB + resolvedR;
		}

	private:
		Value _top;
		Value _right;
		Value _bottom;
		Value _left;
		float _oldMargin;
	};

	class dt_api Padding : public Style<Value, Value, Value, Value>
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

			if (_top.Unit == UnitType::Percent)
			{
				YGNodeStyleSetPaddingPercent((YGNodeRef)element->GetLayoutEngineHandle(),
											YGEdgeTop, _top.Val);
			}
			else
			{
				YGNodeStyleSetPadding((YGNodeRef)element->GetLayoutEngineHandle(),
									 YGEdgeTop, resolvedT);
			}

			if (_bottom.Unit == UnitType::Percent)
			{
				YGNodeStyleSetPaddingPercent((YGNodeRef)element->GetLayoutEngineHandle(),
											YGEdgeBottom, _bottom.Val);
			}
			else
			{
				YGNodeStyleSetPadding((YGNodeRef)element->GetLayoutEngineHandle(),
									 YGEdgeBottom, resolvedB);
			}

			if (_right.Unit == UnitType::Percent)
			{
				YGNodeStyleSetPaddingPercent((YGNodeRef)element->GetLayoutEngineHandle(),
											YGEdgeRight, _right.Val);
			}
			else
			{
				YGNodeStyleSetPadding((YGNodeRef)element->GetLayoutEngineHandle(),
									 YGEdgeRight, resolvedR);
			}

			if (_left.Unit == UnitType::Percent)
			{
				YGNodeStyleSetPaddingPercent((YGNodeRef)element->GetLayoutEngineHandle(),
											YGEdgeLeft, _left.Val);
			}
			else
			{
				YGNodeStyleSetPadding((YGNodeRef)element->GetLayoutEngineHandle(),
									 YGEdgeLeft, resolvedL);
			}

			_oldMargin = resolvedT + resolvedL + resolvedB + resolvedR;
		}

	private:
		Value _top;
		Value _right;
		Value _bottom;
		Value _left;
		float _oldMargin;
	};

	class dt_api Position : public Style<Value, Value, Value, Value>
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

			if (_top.Unit == UnitType::Percent)
			{
				YGNodeStyleSetPositionPercent((YGNodeRef)element->GetLayoutEngineHandle(),
											 YGEdgeTop, _top.Val);
			}
			else
			{
				YGNodeStyleSetPosition((YGNodeRef)element->GetLayoutEngineHandle(),
									  YGEdgeTop, resolvedT);
			}

			if (_bottom.Unit == UnitType::Percent)
			{
				YGNodeStyleSetPositionPercent((YGNodeRef)element->GetLayoutEngineHandle(),
											 YGEdgeBottom, _bottom.Val);
			}
			else
			{
				YGNodeStyleSetPosition((YGNodeRef)element->GetLayoutEngineHandle(),
									  YGEdgeBottom, resolvedB);
			}

			if (_right.Unit == UnitType::Percent)
			{
				YGNodeStyleSetPositionPercent((YGNodeRef)element->GetLayoutEngineHandle(),
											 YGEdgeRight, _right.Val);
			}
			else
			{
				YGNodeStyleSetPosition((YGNodeRef)element->GetLayoutEngineHandle(),
									  YGEdgeRight, resolvedR);
			}

			if (_left.Unit == UnitType::Percent)
			{
				YGNodeStyleSetPositionPercent((YGNodeRef)element->GetLayoutEngineHandle(),
											 YGEdgeLeft, _left.Val);
			}
			else
			{
				YGNodeStyleSetPosition((YGNodeRef)element->GetLayoutEngineHandle(),
									  YGEdgeLeft, resolvedL);
			}

			_oldMargin = resolvedT + resolvedL + resolvedB + resolvedR;
		}

	private:
		Value _top;
		Value _right;
		Value _bottom;
		Value _left;
		float _oldMargin;
	};

	class dt_api AlignContent : public Style<Drift::Align>
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

		[[nodiscard]] auto GetValue(Element* element) const -> Drift::Align
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

	class dt_api AlignItems : public Style<Drift::Align>
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

		[[nodiscard]] auto GetValue(Element* element) const -> Drift::Align
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

	class dt_api AlignSelf : public Style<Drift::Align>
	{
	public:
		[[nodiscard]] inline auto StyleName() const -> std::string override
		{
			return "align-self";
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

		[[nodiscard]] auto GetValue(Element* element) const -> Drift::Align
		{
			return _val;
		}

		void RecalculateLayout(Element* element) override
		{
			if (_val == _oldVal)
			{
				return;
			}

			YGNodeStyleSetAlignSelf((YGNodeRef)element->GetLayoutEngineHandle(),
									 (YGAlign)_val);
			_oldVal = _val;
		}

	private:
		Drift::Align _val;
		Drift::Align _oldVal;
	};

	class dt_api JustifyContent : public Style<Drift::Justify>
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

		[[nodiscard]] auto GetValue(Element* element) const -> Drift::Justify
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

	class dt_api Display : public Style<Drift::DisplayType>
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

		[[nodiscard]] auto GetValue(Element* element) const -> Drift::DisplayType
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

	class dt_api Overflow : public Style<Drift::OverflowType>
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

		[[nodiscard]] auto GetValue(Element* element) const -> Drift::OverflowType
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

	class dt_api FlexWrap : public Style<Drift::WrapType>
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

		[[nodiscard]] auto GetValue(Element* element) const -> Drift::WrapType
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

	class dt_api FlexDirection : public Style<Drift::Direction>
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

		[[nodiscard]] auto GetValue(Element* element) const -> Drift::Direction
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

	class dt_api PositionType : public Style<Drift::PositionType>
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

		[[nodiscard]] auto GetValue(Element* element) const -> Drift::PositionType
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

	class dt_api BoxSizing : public Style<Drift::BoxSizingType>
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

		[[nodiscard]] auto GetValue(Element* element) const -> Drift::BoxSizingType
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