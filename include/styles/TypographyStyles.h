#pragma once
#include "core/FontManager.h"
#include "core/SkTypeface.h"
#include "styles/Style.h"
#include "core/Element.h"
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
			element->EmitSignal("typography.changed");
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

		[[nodiscard]] auto GetValue(Element* element) const -> SkTypeface*
		{
			return _font;
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
			_font = FontManager::GetFont(FontManager::ResolveFontStack(val));
			element->EmitSignal("typography.changed");
			Dirty = false;
		}

	private:
		SkTypeface* _font;
	};
}