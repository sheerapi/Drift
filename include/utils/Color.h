#pragma once
#include "core/Macros.h"
#include <algorithm>
#include <string>

namespace Drift
{
	struct dt_api Color
	{
	public:
		float R{0};
		float G{0};
		float B{0};
		float A{255};

		Color() = default;
		Color(float red, float green, float blue, float alpha = 255)
			: R(std::clamp(red, 0.F, 255.F)), G(std::clamp(green, 0.F, 255.F)),
			  B(std::clamp(blue, 0.F, 255.F)), A(std::clamp(alpha, 0.F, 255.F)) {};

		inline auto operator==(const Color& other) const -> bool
		{
			return R == other.R && G == other.G && B == other.B && A == other.A;
		}

		inline auto operator!=(const Color& other) const -> bool
		{
			return !(*this == other);
		}

		[[nodiscard]] inline auto ToHex() -> unsigned int
		{
			R = std::clamp(R, 0.F, 255.F);
			G = std::clamp(G, 0.F, 255.F);
			B = std::clamp(B, 0.F, 255.F);
			A = std::clamp(A, 0.F, 255.F);
			return ((int)A << 24) | ((int)R << 16) | ((int)G << 8) | (int)B;
		}

		[[nodiscard]] inline auto ToFloatArray() const -> float*
		{
			return new float[4]{(float)R / 255.0F, (float)G / 255.0F, (float)B / 255.0F,
								(float)A / 255.0F};
		}

		[[nodiscard]] inline auto ToIntArray() const -> float*
		{
			return new float[4]{R, G, B, A};
		}

		[[nodiscard]] static inline auto RandomColor() -> Color
		{
			return {static_cast<float>(static_cast<float>(rand()) /
									   static_cast<float>(RAND_MAX) * 255),
					static_cast<float>(static_cast<float>(rand()) /
									   static_cast<float>(RAND_MAX) * 255),
					static_cast<float>(static_cast<float>(rand()) /
									   static_cast<float>(RAND_MAX) * 255)};
		}

		[[nodiscard]] static inline auto FromHex(unsigned int hex) -> Color
		{
			return {
				static_cast<float>((hex >> 16) & 0xFF), // Red
				static_cast<float>((hex >> 8) & 0xFF),	// Green
				static_cast<float>(hex & 0xFF),			// Blue
				static_cast<float>(((hex & 0xFF000000) != 0U) ? ((hex >> 24) & 0xFF)
															  : 255) // Alpha
			};
		}

		[[nodiscard]] static inline auto FromFloatArray(const float* arr) -> Color
		{
			return {(float)(arr[0] * 255), (float)(arr[1] * 255), (float)(arr[2] * 255),
					(float)(arr[3] * 255)};
		}

		[[nodiscard]] static inline auto FromIntArray(float* arr) -> Color
		{
			return {arr[0], arr[1], arr[2], arr[3]};
		}

		[[nodiscard]] static inline auto FromString(const std::string& str) -> Color
		{
			if (str[0] == '#')
			{
				return FromHex(std::stoul(str.substr(1), nullptr, 16));
			}

			return FromIntArray(
				new float[4]{static_cast<float>(std::stoi(str.substr(0, 3))),
							 static_cast<float>(std::stoi(str.substr(3, 3))),
							 static_cast<float>(std::stoi(str.substr(6, 3))),
							 static_cast<float>(std::stoi(str.substr(9, 3)))});
		}
	};
}