#pragma once
#include "core/Element.h"
#include "core/Logger.h"
#include "styles/Style.h"
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

		void ApplyEdits(Element* element, Value val) override
		{
			if (StyleBase::IsReadyToResolve(element))
			{
				Internals::animateValue(&_width.Val, val.Resolve(element), element);
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

			if (_width.Unit != UnitType::Pixels)
			{
				_width.Unit = UnitType::Pixels;
				_width.Val = resolved;
			}

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

		void ApplyEdits(Element* element, Value val) override
		{
			if (StyleBase::IsReadyToResolve(element))
			{
				Internals::animateValue(&_width.Val, val.Resolve(element), element);
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

			if (_width.Unit != UnitType::Pixels)
			{
				_width.Unit = UnitType::Pixels;
				_width.Val = resolved;
			}

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

		void ApplyEdits(Element* element, Value val) override
		{
			if (StyleBase::IsReadyToResolve(element))
			{
				Internals::animateValue(&_width.Val, val.Resolve(element), element);
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

			if (_width.Unit != UnitType::Pixels)
			{
				_width.Unit = UnitType::Pixels;
				_width.Val = resolved;
			}

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

		void ApplyEdits(Element* element, Value val) override
		{
			if (StyleBase::IsReadyToResolve(element))
			{
				Internals::animateValue(&_width.Val, val.Resolve(element), element);
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

			if (_width.Unit != UnitType::Pixels)
			{
				_width.Unit = UnitType::Pixels;
				_width.Val = resolved;
			}

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

		void ApplyEdits(Element* element, Value val) override
		{
			if (StyleBase::IsReadyToResolve(element))
			{
				Internals::animateValue(&_width.Val, val.Resolve(element), element);
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

			if (_width.Unit != UnitType::Pixels)
			{
				_width.Unit = UnitType::Pixels;
				_width.Val = resolved;
			}

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

		void ApplyEdits(Element* element, Value val) override
		{
			if (StyleBase::IsReadyToResolve(element))
			{
				Internals::animateValue(&_width.Val, val.Resolve(element), element);
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

			if (_width.Unit != UnitType::Pixels)
			{
				_width.Unit = UnitType::Pixels;
				_width.Val = resolved;
			}

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

		void ApplyEdits(Element* element, Value val) override
		{
			if (StyleBase::IsReadyToResolve(element))
			{
				Internals::animateValue(&_width.Val, val.Resolve(element), element);
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
					(element->GetParent()->FlexDirection() == FlexDirection::Row ||
					 element->GetParent()->FlexDirection() == FlexDirection::RowReverse)
						? PreferredDimension::Width
						: PreferredDimension::Height;
			}

			auto resolved = _width.Resolve(element, dimension);

			if (_width.Unit != UnitType::Pixels)
			{
				_width.Unit = UnitType::Pixels;
				_width.Val = resolved;
			}

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

	class Gap : public Style<Value, Value>
	{
	public:
		[[nodiscard]] inline auto StyleName() const -> std::string override
		{
			return "gap";
		}

		void ApplyEdits(Element* element, Value val, Value val2) override
		{
			if (StyleBase::IsReadyToResolve(element))
			{
				Internals::animateValue(&_gapHorizontal.Val, val.Resolve(element),
										element);
				Internals::animateValue(&_gapVertical.Val, val2.Resolve(element),
										element);
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

			if (_gapHorizontal.Unit != UnitType::Pixels)
			{
				_gapHorizontal.Unit = UnitType::Pixels;
				_gapHorizontal.Val = gapH;
			}

			if (_gapVertical.Unit != UnitType::Pixels)
			{
				_gapVertical.Unit = UnitType::Pixels;
				_gapVertical.Val = gapV;
			}

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
}