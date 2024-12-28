#include "core/FontManager.h"
#include "core/Application.h" // IWYU pragma: keep
#include "core/Logger.h"
#include "core/SkFontMgr.h"
#include "core/WorkerScheduler.h"
#include "fontconfig/fontconfig.h"
#include "ports/SkFontMgr_empty.h"
#include "utils/ConfigManager.h"
#include "utils/PerformanceTimer.h"
#include <cctype>

namespace Drift
{
	void FontManager::Init()
	{
		dt_stopwatch();

		fontMgr = SkFontMgr_New_Custom_Empty();

		fonts["sans-serif"] = GetFont(
			ResolveFontStack({ConfigManager::HasGlobalValue("fonts.sans_serif")
								  ? ConfigManager::GetGlobalString("fonts.sans_serif")
								  : "Inter",
							  "sans"}),
			nullptr);

		fonts["serif"] =
			GetFont(ResolveFontStack({ConfigManager::HasGlobalValue("fonts.serif")
										  ? ConfigManager::GetGlobalString("fonts.serif")
										  : "Playfair Display",
									  "serif"}),
					nullptr);

		fonts["monospaced"] = GetFont(
			ResolveFontStack({ConfigManager::HasGlobalValue("fonts.monospaced")
								  ? ConfigManager::GetGlobalString("fonts.monospaced")
								  : "Roboto Mono",
							  "monospaced"}),
			nullptr);

		if (ConfigManager::HasGlobalValue("fonts.fallback"))
		{
			auto fallbackFonts = ConfigManager::GetGlobalStringArray("fonts.fallback");

			for (auto& font : fallbackFonts)
			{
				GetFont(font, nullptr);
			}
		}

		dt_coreVerbose("Loaded {} fonts", fonts.size());
	}

	auto FontManager::ResolveFontStack(const std::vector<std::string>& stack)
		-> std::string
	{
		for (const auto& font : stack)
		{
			if (HasFont(font))
			{
				return font;
			}
		}

		return "sans-serif";
	}

	auto FontManager::GetFont(const std::string& name, Element* element) -> Font*
	{
		if (fonts.contains(name))
		{
			return fonts[name];
		}

		if (!HasFont(name))
		{
			dt_coreError("Font {} was not found in the system!", name);
			fonts[name] =
				new Font(std::make_shared<sk_sp<SkTypeface>>(SkTypeface::MakeEmpty()));
			return fonts[name];
		}

		auto* pattern = FcNameParse((const FcChar8*)name.c_str());
		FcConfigSubstitute(nullptr, pattern, FcMatchPattern);
		FcDefaultSubstitute(pattern);

		FcResult result;
		FcPattern* match = FcFontMatch(nullptr, pattern, &result);

		FcChar8* filePath = nullptr;
		FcChar8* family = nullptr;
		FcPatternGetString(match, FC_FILE, 0, &filePath);
		FcPatternGetString(match, FC_FAMILY, 0, &family);

		fonts[std::string(reinterpret_cast<char*>(family))] =
			new Font(std::make_shared<sk_sp<SkTypeface>>(SkTypeface::MakeEmpty()));

		Internals::WorkerScheduler::AddTask(
			[family, filePath, element]()
			{
				*fonts[std::string(reinterpret_cast<char*>(family))] =
					*new Font(std::make_shared<sk_sp<SkTypeface>>(
						fontMgr->makeFromFile(reinterpret_cast<char*>(filePath))));
				dt_coreVerbose("Loaded font {}", reinterpret_cast<char*>(family));

				if (element != nullptr)
				{
					element->EmitSignal("asset.loaded");
				}
			});

		FcPatternDestroy(pattern);
		return fonts[std::string(reinterpret_cast<char*>(family))];
	}

	auto FontManager::HasFont(const std::string& name) -> bool
	{
		FcInitBringUptoDate();

		auto* pattern = FcNameParse((const FcChar8*)name.c_str());
		FcConfigSubstitute(nullptr, pattern, FcMatchPattern);
		FcDefaultSubstitute(pattern);

		FcResult result;
		FcPattern* match = FcFontMatch(nullptr, pattern, &result);

		bool found = (match != nullptr);

		if (match != nullptr)
		{
			FcPatternDestroy(match);
		}

		FcPatternDestroy(pattern);

		return found;
	}

	auto FontManager::FindFallbackFont(uint32_t codepoint) -> Font*
	{
		std::vector<std::string> fallbackFonts;

		if (ConfigManager::HasGlobalValue("fonts.fallback"))
		{
			fallbackFonts = ConfigManager::GetGlobalStringArray("fonts.fallback");
		}

		for (const auto& fontName : fallbackFonts)
		{
			auto* font = GetFont(fontName, nullptr);

			if (HasGlyph(font, codepoint))
			{
				return font;
			}
		}

		return GetFont("sans-serif", nullptr);
	}

	auto FontManager::RequiresFallback(uint32_t codepoint) -> bool
	{
		return (codepoint >= 0x1F300 &&
				codepoint <= 0x1F5FF) || // Misc Symbols and Pictographs
			   (codepoint >= 0x1F600 && codepoint <= 0x1F64F) || // Emoticons
			   (codepoint >= 0x1F680 && codepoint <= 0x1F6FF);
	}

	auto FontManager::HasGlyph(Font* typeface, uint32_t codepoint) -> bool
	{
		if (typeface->GlyphCache.find(codepoint) != typeface->GlyphCache.end())
		{
			return typeface->GlyphCache[codepoint];
		}
		bool hasGlyph = typeface->Typeface->get()->unicharToGlyph(codepoint) != 0;
		typeface->GlyphCache[codepoint] = hasGlyph;
		return hasGlyph;
	}

	auto FontManager::CanGlyphRender(char character) -> bool
	{
		return character != '\n' && character != '\t' && character != '\r' &&
			   character != '\0';
	}
}