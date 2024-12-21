#include "utils/CubicBezier.h"

namespace Drift
{
	auto CubicBezier::Evaluate(float t) const -> float
	{
		return SampleBezier(Y1, Y2, _solveForX(t));
	}

	auto CubicBezier::SampleBezier(float p1, float p2, float t) -> float
	{
		float u = 1 - t;
		return (3 * u * u * t * p1) + (3 * u * t * t * p2) + (t * t * t);
	}

	auto CubicBezier::_solveForX(float t) const -> float
	{
		const float Epsilon = 0.00001F; // Precision
		float guess = t;

		for (int i = 0; i < 10; ++i) // Limit iterations
		{
			float x = SampleBezier(X1, X2, guess) - t;
			if (std::abs(x) < Epsilon)
			{
				return guess;
			}

			float dx = BezierDerivative(X1, X2, guess);
			if (std::abs(dx) < Epsilon)
			{
				break;
			}

			guess -= x / dx;
		}

		return guess;
	}

	auto CubicBezier::BezierDerivative(float p1, float p2, float t) -> float
	{
		float u = 1 - t;
		return (3 * u * u * p1) + (6 * u * t * (p2 - p1)) + (3 * t * t * (1 - p2));
	}
}