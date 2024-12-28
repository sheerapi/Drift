#pragma once
#include "core/FontManager.h"
#include "core/SkTypeface.h"
#include "styles/Style.h"
#include "core/Element.h"
#include "yoga/YGNode.h"
#include <vector>

namespace Drift::Styling
{
	class dt_api FontSize : public Style<Value>
	{
    public:
        void ApplyEdits(Element *element, Value val) override
        {
			if (IsReadyToResolve(element))
			{
				Internals::animateValue(&_size.Val, _size.Convert(val.Unit, element), val.Val, element);
			}
			else
			{
				_size.Val = val.Val;
				_size.Unit = val.Unit;
			}
			Dirty = false;
		}

		[[nodiscard]] auto GetValue(Element* element) const -> float
		{
			return _size.Resolve(element);
		}

		[[nodiscard]] inline auto StyleName() const -> std::string override
		{
			return "font-size";
		}

		[[nodiscard]] inline auto StylePriority() const -> int override
		{
			return 5;
		}

		[[nodiscard]] inline auto IsInheritable() const -> bool override
		{
			return true;
		}

	private:
        Value _size;
    };

    class dt_api FontFamily : public Style<std::vector<std::string>>
    {
    public:
		[[nodiscard]] inline auto StyleName() const -> std::string override
		{
			return "font-family";
		}

		[[nodiscard]] inline auto StylePriority() const -> int override
		{
			return 5;
		}

		[[nodiscard]] auto GetValue(Element* element) const -> sk_sp<SkTypeface>
		{
			return *_font->Typeface;
		}

		[[nodiscard]] inline auto IsAnimatable() const -> bool override
		{
			return false;
		}

		[[nodiscard]] inline auto IsInheritable() const -> bool override
		{
			return true;
		}

		void ApplyEdits(Element* element, std::vector<std::string> val) override
		{
			_font = FontManager::GetFont(FontManager::ResolveFontStack(val), element);
			Dirty = false;
		}

	private:
		Font* _font;
	};

	class dt_api LineHeight : public Style<float>
	{
	public:
		void ApplyEdits(Element* element, float val) override
		{
			Internals::animateValue(&_height, _height, val, element);
			Dirty = false;
		}

		[[nodiscard]] auto GetValue(Element* element) const -> float
		{
			return _height;
		}

		[[nodiscard]] inline auto StyleName() const -> std::string override
		{
			return "line-height";
		}

		[[nodiscard]] inline auto StylePriority() const -> int override
		{
			return 5;
		}

		[[nodiscard]] inline auto IsInheritable() const -> bool override
		{
			return true;
		}

		void RecalculateLayout(Element* element) override
		{
			if (_height == _oldHeight)
			{
				return;
			}

			if (YGNodeHasMeasureFunc((YGNodeRef)element->GetLayoutEngineHandle()))
			{
				YGNodeMarkDirty((YGNodeRef)element->GetLayoutEngineHandle());
			}
			_oldHeight = _height;
		}

	private:
		float _height;
		float _oldHeight;
	};

	class dt_api LetterSpacing : public Style<Value>
	{
	public:
		void ApplyEdits(Element* element, Value val) override
		{
			if (IsReadyToResolve(element))
			{
				Internals::animateValue(&_size.Val, _size.Convert(val.Unit, element),
										val.Val, element);
			}
			else
			{
				_size.Val = val.Val;
				_size.Unit = val.Unit;
			}
			Dirty = false;
		}

		[[nodiscard]] auto GetValue(Element* element) const -> float
		{
			return _size.Resolve(element);
		}

		[[nodiscard]] inline auto StyleName() const -> std::string override
		{
			return "letter-spacing";
		}

		[[nodiscard]] inline auto StylePriority() const -> int override
		{
			return 5;
		}

		[[nodiscard]] inline auto IsInheritable() const -> bool override
		{
			return true;
		}

		void RecalculateLayout(Element* element) override
		{
			auto resolved = _size.Resolve(element);

			if (resolved == _oldSize)
			{
				return;
			}

			if (YGNodeHasMeasureFunc((YGNodeRef)element->GetLayoutEngineHandle()))
			{
				YGNodeMarkDirty((YGNodeRef)element->GetLayoutEngineHandle());
			}
			_oldSize = resolved;
		}

	private:
		Value _size;
		float _oldSize;
	};
}