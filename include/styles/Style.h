#pragma once
#include <string>

namespace Drift
{
	class Element;

	namespace Styling
	{
		class StyleBase
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

			[[nodiscard]] inline auto IsDirty() const -> bool
			{
				return Dirty;
			}

			virtual void RecalculateLayout(Element* element) {};
			virtual void BeginDrawStyle(Element* element) {};
			virtual void EndDrawStyle(Element* element) {};

			template <typename... Args> void EditStyle(Args... args) {};

		protected:
			bool Dirty{true};
		};

		template <typename... Args> class Style : public StyleBase
		{
		public:
			[[nodiscard]] auto StyleName() const -> std::string override
			{
				return "style";
			}

			void EditStyle(Args... args)
			{
				ApplyEdits(args...);
			}

		protected:
			virtual void ApplyEdits(Args... args) = 0;
		};

        enum class PreferredDimension
        {
            Width,
            Height
        };

        enum class UnitType
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

        struct Value
        {
        public:
            float Value;
            UnitType Unit;

            auto Resolve(Element* element, PreferredDimension dimension = PreferredDimension::Width) const -> float;
        };
	}
}