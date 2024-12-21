#include "styles/Style.h"
#include "core/Activity.h"
#include "core/Element.h"
#include "core/Logger.h"
#include "core/View.h"
#include "styles/AnimationScheduler.h"
#include "styles/AnimationStyles.h"
#include "styles/TransitionFunction.h"
#include "utils/Demangle.h"

namespace Drift::Styling
{
	auto Value::Resolve(Element* element, PreferredDimension dimension) const -> float
	{
		switch (Unit)
		{
		case UnitType::Pixels:
			return Value;

		case UnitType::Em:
			// TODO;
			return Value * 16;

		case UnitType::Rem:
			// TODO;
			return Value * 16;

		case UnitType::Ex:
			// TODO;
			return Value * 8;

		case UnitType::Ch:
			// TODO;
			return Value * 8;

		case UnitType::Vw:
			return element->GetContainingActivity()
					   ->GetContainingView()
					   ->GetBoundingBox()
					   .Width *
				   (Value / 100);

		case UnitType::Vh:
			return element->GetContainingActivity()
					   ->GetContainingView()
					   ->GetBoundingBox()
					   .Height *
				   (Value / 100);

		case UnitType::Vmin:
			return std::min(element->GetContainingActivity()
								->GetContainingView()
								->GetBoundingBox()
								.Width,
							element->GetContainingActivity()
								->GetContainingView()
								->GetBoundingBox()
								.Height) *
				   (Value / 100);

		case UnitType::Vmax:
			return std::max(element->GetContainingActivity()
								->GetContainingView()
								->GetBoundingBox()
								.Width,
							element->GetContainingActivity()
								->GetContainingView()
								->GetBoundingBox()
								.Height) *
				   (Value / 100);

		case UnitType::Percent:
		{
			if (!element->IsOrphan())
			{
				return dimension == PreferredDimension::Width
						   ? element->GetParent()->GetPercentWidth(Value)
						   : element->GetParent()->GetPercentHeight(Value);
			}

			return dimension == PreferredDimension::Width
					   ? element->GetPercentWidth(Value)
					   : element->GetPercentHeight(Value);
		}

		case UnitType::Centimeters:
            return Value * 37.7952755906F;

		case UnitType::Millimeters:
            return Value * 3.77952755906F;

		case UnitType::Inches:
            return Value * 96;

		case UnitType::Points:
            return Value * 1.33333333333F;

		case UnitType::Picas:
            return Value * 16;
		}

		return Value;
	}

	namespace Internals
	{
		void animateValue(float* value, float target, Element* element)
		{
			if (element->HasStyle<TransitionEasingFunction>() &&
				element->HasStyle<TransitionDuration>())
			{
				auto duration = element->GetStyle<TransitionDuration>()->GetValue();
				auto* easing = element->GetStyle<TransitionEasingFunction>()->GetValue();

				auto animation = Animation();
				animation.Easing = easing;
				animation.Value = value;
				animation.Duration = duration;
				animation.Start = *value;
				animation.Target = target;

				AnimationScheduler::Submit(animation);
			}
			else
			{
				(*value) = target;
			}
		}
	}
}