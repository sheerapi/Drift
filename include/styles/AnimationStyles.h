#pragma once
#include "Style.h"
#include "core/Macros.h"

namespace Drift::Styling
{
    enum class dt_api TimeUnit
    {
        Milliseconds,
        Seconds,
        Minutes,
        Hours
    };

	class dt_api TransitionDuration : public Style<unsigned int, TimeUnit>
	{
	public:
		[[nodiscard]] inline auto StyleName() const -> std::string override
		{
			return "transition-duration";
		}

		void ApplyEdits(Element* element, unsigned duration, TimeUnit unit = TimeUnit::Milliseconds) override
		{
			auto result = duration;

            switch (unit)
            {
                case TimeUnit::Seconds:
                    result *= 1000;
                    break;
                case TimeUnit::Minutes:
                    result *= 60000;
                    break;
                case TimeUnit::Hours:
                    result *= 3600000;
                    break;
                default:
                    break;
            };

            _duration = result;
			Dirty = false;
		}

		[[nodiscard]] auto IsAnimatable() const -> bool override
		{
			return false;
		}

	private:
		unsigned int _duration;
	};
}