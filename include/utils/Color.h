#pragma once
#include "core/Macros.h"
#include <string>

namespace Drift
{
	struct dt_api Color
	{
	public:
		int R{0};
		int G{0};
		int B{0};
		int A{255};

		Color() = default;
		Color(int red, int green, int blue, int alpha = 255)
			: R(red), G(green), B(blue), A(alpha) {};

		inline auto operator==(const Color& other) const -> bool
		{
			return R == other.R && G == other.G && B == other.B && A == other.A;
		}

		inline auto operator!=(const Color& other) const -> bool
		{
			return !(*this == other);
		}

		[[nodiscard]] inline auto ToHex() const -> unsigned int
		{
			return (A << 24) | (R << 16) | (G << 8) | B;
		}

		[[nodiscard]] inline auto ToFloatArray() const -> float*
		{
			return new float[4]{(float)R / 255.0F, (float)G / 255.0F, (float)B / 255.0F,
								(float)A / 255.0F};
		}

		[[nodiscard]] inline auto ToIntArray() const -> int*
		{
			return new int[4]{R, G, B, A};
		}

		[[nodiscard]] static inline auto RandomColor() -> Color
		{
			return {static_cast<int>(static_cast<float>(rand()) /
									 static_cast<float>(RAND_MAX) * 255),
					static_cast<int>(static_cast<float>(rand()) /
									 static_cast<float>(RAND_MAX) * 255),
					static_cast<int>(static_cast<float>(rand()) /
									 static_cast<float>(RAND_MAX) * 255)};
		}

		[[nodiscard]] static inline auto FromHex(unsigned int hex) -> Color
		{
			return {
				static_cast<int>((hex >> 16) & 0xFF), // Red
				static_cast<int>((hex >> 8) & 0xFF),  // Green
				static_cast<int>(hex & 0xFF),		  // Blue
				static_cast<int>(((hex & 0xFF000000) != 0U) ? ((hex >> 24) & 0xFF)
															: 255) // Alpha
			};
		}

		[[nodiscard]] static inline auto FromFloatArray(const float* arr) -> Color
		{
			return {(int)(arr[0] * 255), (int)(arr[1] * 255), (int)(arr[2] * 255),
					(int)(arr[3] * 255)};
		}

		[[nodiscard]] static inline auto FromIntArray(int* arr) -> Color
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
				new int[4]{std::stoi(str.substr(0, 3)), std::stoi(str.substr(3, 3)),
						   std::stoi(str.substr(6, 3)), std::stoi(str.substr(9, 3))});
		}
	};
}