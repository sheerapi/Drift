#pragma once
#include "core/Element.h"
#include "core/Macros.h"
#include "core/SkFontMgr.h"
#include "core/SkTypeface.h"
#include "src/ports/SkFontMgr_custom.h"
#include <cstdint>
#include <fontconfig/fontconfig.h>
#include <string>
#include <unordered_map>
#include <vector>

namespace Drift
{
	struct Font
	{
	public:
		std::shared_ptr<sk_sp<SkTypeface>> Typeface;
		std::unordered_map<uint32_t, bool> GlyphCache;

		Font(const std::shared_ptr<sk_sp<SkTypeface>>& typeface) : Typeface(typeface) {};
	};

	class dt_api FontManager
	{
	public:
		static void Init();
		static auto HasFont(const std::string& name) -> bool;
		static auto ResolveFontStack(const std::vector<std::string>& stack)
			-> std::string;
		static auto GetFont(const std::string& name, Element* element) -> Font*;
		static auto FindFallbackFont(uint32_t codepoint) -> Font*;
		static void Shutdown();
		static auto RequiresFallback(uint32_t codepoint) -> bool;
		static auto HasGlyph(Font* typeface, uint32_t codepoint) -> bool;
		static auto CanGlyphRender(char character) -> bool;

		static inline auto GetFontMgr() -> sk_sp<SkFontMgr>
		{
			return fontMgr;
		}

	private:
		inline static std::unordered_map<std::string, Font*> fonts;
		inline static sk_sp<SkFontMgr> fontMgr;
	};
}