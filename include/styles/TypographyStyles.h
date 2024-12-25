#pragma once
#include "styles/Style.h"
#include <vector>

namespace Drift::Styling
{
    class FontSize : public Style<float>
    {
    public:
        void ApplyEdits(Element *element, float val) override
        {
			Internals::animateValue(&_size, val, element);
            Dirty = false;
		}

		[[nodiscard]] auto GetValue(Element* element) const -> float
		{
			return _size;
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
        float _size;
    };

    class FontFamily : public Style<std::vector<std::string>>
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

		[[nodiscard]] inline auto IsAnimatable() const -> bool override
		{
			return false;
		}

		[[nodiscard]] inline auto IsInheritable() const -> bool override
		{
			return true;
		}
	};
}