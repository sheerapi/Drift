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
		auto result = Val;

		switch (Unit)
		{
		case UnitType::Pixels:
			result = Val;
			break;

		case UnitType::Em:
			// TODO;
			result = Val * 16;
			break;

		case UnitType::Rem:
			// TODO;
			result = Val * 16;
			break;

		case UnitType::Ex:
			// TODO;
			result = Val * 8;
			break;

		case UnitType::Ch:
			// TODO;
			result = Val * 8;
			break;

		case UnitType::Vw:
			result = element->GetContainingActivity()
					   ->GetContainingView()
					   ->GetBoundingBox()
					   .Width *
				   (Val / 100);
			break;

		case UnitType::Vh:
			result = element->GetContainingActivity()
					   ->GetContainingView()
					   ->GetBoundingBox()
					   .Height *
				   (Val / 100);
			break;

		case UnitType::Vmin:
			result = std::min(element->GetContainingActivity()
								->GetContainingView()
								->GetBoundingBox()
								.Width,
							element->GetContainingActivity()
								->GetContainingView()
								->GetBoundingBox()
								.Height) *
				   (Val / 100);
			break;

		case UnitType::Vmax:
			result = std::max(element->GetContainingActivity()
								->GetContainingView()
								->GetBoundingBox()
								.Width,
							element->GetContainingActivity()
								->GetContainingView()
								->GetBoundingBox()
								.Height) *
				   (Val / 100);
			break;

		case UnitType::Percent:
		{
			if (!element->IsOrphan())
			{
				result = dimension == PreferredDimension::Width
						   ? element->GetParent()->GetPercentWidth(Val)
						   : element->GetParent()->GetPercentHeight(Val);

				break;
			}

			result = dimension == PreferredDimension::Width
					   ? element->GetPercentWidth(Val)
					   : element->GetPercentHeight(Val);
			break;
		}

		case UnitType::Centimeters:
			result = Val * 37.7952755906F;
			break;

		case UnitType::Millimeters:
			result = Val * 3.77952755906F;
			break;

		case UnitType::Inches:
			result = Val * 96;
			break;

		case UnitType::Points:
			result = Val * 1.33333333333F;
			break;

		case UnitType::Picas:
			result = Val * 16;
			break;
		}

		return result;
	}

	auto StyleBase::IsReadyToResolve(Element* element) -> bool
	{
		if (element == nullptr)
		{
			return false;
		}

		if (element->GetContainingActivity() == nullptr)
		{
			return false;
		}

		if (element->GetContainingActivity()->GetContainingView() == nullptr)
		{
			return false;
		}
		
		return true;
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