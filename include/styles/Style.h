#pragma once
#include "core/Logger.h"
#include <string>

namespace Drift
{
	class Element;

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

	class StyleTest : public Style<unsigned int>
	{
	public:
		StyleTest(unsigned int test = 0)
		{
		}

		[[nodiscard]] auto StyleName() const -> std::string override
		{
			return "style-test";
		}

		inline void RecalculateLayout(Element* element) override
		{
            dt_coreInfo("Recalculated layout for element");
            Dirty = false;
		}

	protected:
		inline void ApplyEdits(unsigned int test) override
		{
			dt_coreInfo("Edited style to {}", test);
		}
	};
}