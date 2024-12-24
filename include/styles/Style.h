#pragma once
#include "core/Logger.h"
#include "core/Macros.h"
#include "core/SkCanvas.h"
#include <string>

namespace Drift
{
	class Element;

	namespace Styling
	{
		class dt_api StyleBase
		{
		public:
			StyleBase() = default;
			virtual ~StyleBase() = default;

			[[nodiscard]] virtual auto StyleName() const -> std::string = 0;
			[[nodiscard]] virtual auto StylePriority() const -> int
			{
				return 0;
			}

			[[nodiscard]] virtual auto IsInheritable() const -> bool
			{
				return false;
			}

			[[nodiscard]] virtual auto IsAnimatable() const -> bool
			{
				return true;
			}

			[[nodiscard]] inline auto IsDirty() const -> bool
			{
				return Dirty;
			}

			virtual void RecalculateLayout(Element* element) {};

			// since apparently using the global context causes a segfault
			// because whenever this is called it is magically reset to nullptr
			// i do NOT understand this shit
			virtual void BeginDrawStyle(Element* element, SkCanvas* ctx) {};
			virtual void EndDrawStyleGroup(Element* element, SkCanvas* ctx) {};
			virtual void EndDrawStyle(Element* element, SkCanvas* ctx) {};

			static auto IsReadyToResolve(Element* element) -> bool;

			template <typename... Args> void EditStyle(Element* element, Args... args) {};

		protected:
			bool Dirty{true};
		};

		template <typename... Args> class dt_api Style : public StyleBase
		{
		public:
			[[nodiscard]] auto StyleName() const -> std::string override
			{
				return "style";
			}

			void EditStyle(Element* element, Args... args)
			{
				ApplyEdits(element, args...);
			}

		protected:
			virtual void ApplyEdits(Element* element, Args... args) = 0;
		};

		enum class dt_api PreferredDimension
		{
			Width,
			Height
		};

		enum class dt_api UnitType
		{
			Pixels,
			Em,
			Rem,
			Ex,
			Ch,
			Vw,
			Vh,
			Vmin,
			Vmax,
			Percent,
			Centimeters,
			Millimeters,
			Inches,
			Points,
			Picas
		};

		struct dt_api Value
		{
		public:
			float Val;
			UnitType Unit;

			Value() = default;
			Value(float val, UnitType unit = UnitType::Pixels) : Val(val), Unit(unit) {};

			auto Resolve(Element* element, PreferredDimension dimension =
											   PreferredDimension::Width) const -> float;

			auto Convert(UnitType unit, Element* element, PreferredDimension dimension =
											   PreferredDimension::Width) -> float;
		};

		namespace Internals
		{
			void dt_api animateValue(float* value, float target, Element* element);
			void dt_api animateValue(float* value, float start, float target, Element* element);
		}
	}
}