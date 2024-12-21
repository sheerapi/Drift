#pragma once
#include "core/Macros.h"
#include <cmath>

namespace Drift
{
	struct dt_api CubicBezier
	{
		float X1, Y1, X2, Y2;

		CubicBezier(float cx1, float cy1, float cx2, float cy2)
			: X1(cx1), Y1(cy1), X2(cx2), Y2(cy2)
		{
		}

		[[nodiscard]] auto Evaluate(float t) const -> float;

	private:
		static auto SampleBezier(float p1, float p2, float t) -> float;
		[[nodiscard]] auto _solveForX(float t) const -> float;
		static auto BezierDerivative(float p1, float p2, float t) -> float;
	};
}