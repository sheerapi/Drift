#include "components/activities/ActivityEffect.h"
#include "core/Activity.h"
#include "graphics/RendererContext.h"
#include "core/View.h"
#include "styles/AnimationScheduler.h"

namespace Drift::Components::Activities
{
	void FadeEffect::Present(Activity* activity)
	{
		Styling::AnimationScheduler::AnimateValue(
			&_color.A, 255, activity->GetEasingDuration(), activity->GetEasing());
	}

	void FadeEffect::Shutdown(Activity* activity)
	{
		Styling::AnimationScheduler::AnimateValue(
			&_color.A, 0, activity->GetEasingDuration(), activity->GetEasing());
	}

	void FadeEffect::BeginDraw(Activity* activity)
	{
		dt_canvas->saveLayerAlphaf(nullptr, _color.A / 255);
		dt_canvas->clear(Color(_color.R, _color.G, _color.B, _alpha * 255).ToHex());
	}

	void FadeEffect::EndDraw(Activity* activity)
	{
		dt_canvas->restore();
	}

	void SlideEffect::Present(Activity* activity)
	{
		switch (_direction) 
		{
		case Direction::Left:
			_xPos = -activity->GetContainingView()->GetBoundingBox().Width;
			break;

		case Direction::Right:
			_xPos = activity->GetContainingView()->GetBoundingBox().Width;
			break;

		case Direction::Top:
			_yPos = -activity->GetContainingView()->GetBoundingBox().Height;
			break;

		case Direction::Bottom:
			_yPos = activity->GetContainingView()->GetBoundingBox().Height;
			break;
		}

		Styling::AnimationScheduler::AnimateValue(
			&_xPos, 0, activity->GetEasingDuration(), activity->GetEasing());

		Styling::AnimationScheduler::AnimateValue(&_yPos, 0, activity->GetEasingDuration(),
												 activity->GetEasing());
	}

	void SlideEffect::Shutdown(Activity* activity)
	{
		float newX = 0;
		float newY = 0;

		switch (_direction)
		{
		case Direction::Left:
			newX = -activity->GetContainingView()->GetBoundingBox().Width;
			break;

		case Direction::Right:
			newX = activity->GetContainingView()->GetBoundingBox().Width;
			break;

		case Direction::Top:
			newY = -activity->GetContainingView()->GetBoundingBox().Height;
			break;

		case Direction::Bottom:
			newY = activity->GetContainingView()->GetBoundingBox().Height;
			break;
		}

		Styling::AnimationScheduler::AnimateValue(
			&_xPos, newX, activity->GetEasingDuration(), activity->GetEasing());

		Styling::AnimationScheduler::AnimateValue(
			&_yPos, newY, activity->GetEasingDuration(), activity->GetEasing());
	}

	void SlideEffect::BeginDraw(Activity* activity)
	{
		dt_canvas->save();
		dt_canvas->translate(_xPos, _yPos);
	}

	void SlideEffect::EndDraw(Activity* activity)
	{
		dt_canvas->restore();
	}

	void RotateEffect::Present(Activity* activity)
	{
		Styling::AnimationScheduler::AnimateValue(
			&_degrees, _oldDegrees, 0, activity->GetEasingDuration(), activity->GetEasing());
	}

	void RotateEffect::Shutdown(Activity* activity)
	{
		Styling::AnimationScheduler::AnimateValue(
			&_degrees, _oldDegrees, activity->GetEasingDuration(), activity->GetEasing());
	}

	void RotateEffect::BeginDraw(Activity* activity)
	{
		dt_canvas->save();
		dt_canvas->translate(activity->GetContainingView()->GetBoundingBox().Width / 2,
							 activity->GetContainingView()->GetBoundingBox().Height / 2);

		dt_canvas->rotate(_degrees);

		dt_canvas->translate(-(activity->GetContainingView()->GetBoundingBox().Width / 2),
							 -(activity->GetContainingView()->GetBoundingBox().Height / 2));
	}

	void RotateEffect::EndDraw(Activity* activity)
	{
		dt_canvas->restore();
	}

	void ScaleEffect::Present(Activity* activity)
	{
		Styling::AnimationScheduler::AnimateValue(&_degrees, _oldDegrees, 1,
												  activity->GetEasingDuration(),
												  activity->GetEasing());
	}

	void ScaleEffect::Shutdown(Activity* activity)
	{
		Styling::AnimationScheduler::AnimateValue(
			&_degrees, _oldDegrees, activity->GetEasingDuration(), activity->GetEasing());
	}

	void ScaleEffect::BeginDraw(Activity* activity)
	{
		dt_canvas->save();

		dt_canvas->translate(activity->GetContainingView()->GetBoundingBox().Width / 2,
							 activity->GetContainingView()->GetBoundingBox().Height / 2);

		dt_canvas->scale(_degrees, _degrees);

		dt_canvas->translate(-(activity->GetContainingView()->GetBoundingBox().Width / 2),
							 -(activity->GetContainingView()->GetBoundingBox().Height / 2));
	}

	void ScaleEffect::EndDraw(Activity* activity)
	{
		dt_canvas->restore();
	}
}