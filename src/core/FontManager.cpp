#include "core/FontManager.h"
#include "core/Application.h" // IWYU pragma: keep
#include "core/Logger.h"
#include "core/SkFontMgr.h"
#include "core/WorkerScheduler.h"
#include "fontconfig/fontconfig.h"
#include "ports/SkFontMgr_empty.h"
#include "utils/ConfigManager.h"
#include "utils/PerformanceTimer.h"

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
							  "sans"}), nullptr);

		fonts["serif"] =
			GetFont(ResolveFontStack({ConfigManager::HasGlobalValue("fonts.serif")
										  ? ConfigManager::GetGlobalString("fonts.serif")
										  : "Playfair Display",
									  "serif"}), nullptr);

		fonts["monospaced"] = GetFont(
			ResolveFontStack({ConfigManager::HasGlobalValue("fonts.monospaced")
								  ? ConfigManager::GetGlobalString("fonts.monospaced")
								  : "Roboto Mono",
							  "monospaced"}),
			nullptr);

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
			fonts[name] = new Font(std::make_shared<sk_sp<SkTypeface>>(SkTypeface::MakeEmpty()));
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
					*new Font(std::make_shared<sk_sp<SkTypeface>>(fontMgr->makeFromFile(reinterpret_cast<char*>(filePath))));
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

	auto FontManager::FindFallbackFont(int32_t codepoint) -> Font*
	{
		std::vector<std::string> fallbackFonts;

		if (ConfigManager::HasGlobalValue("fonts.fallback"))
		{
			fallbackFonts = ConfigManager::GetGlobalStringArray("fonts.fallback");
		}

		for (const auto& fontName : fallbackFonts)
		{
			FcPattern* pattern = FcNameParse((const FcChar8*)fontName.c_str());
			FcConfigSubstitute(nullptr, pattern, FcMatchPattern);
			FcDefaultSubstitute(pattern);

			FcCharSet* charSet = FcCharSetCreate();
			FcCharSetAddChar(charSet, codepoint);
			FcPatternAddCharSet(pattern, FC_CHARSET, charSet);
			FcPatternAddBool(pattern, FC_SCALABLE, FcTrue);

			FcResult result;
			FcPattern* matchedPattern = FcFontMatch(nullptr, pattern, &result);
			std::string fontFamily;

			if (matchedPattern != nullptr)
			{
				FcChar8* family = nullptr;
				if (FcPatternGetString(matchedPattern, FC_FAMILY, 0, &family) ==
					FcResultMatch)
				{
					fontFamily = reinterpret_cast<const char*>(family);
					FcPatternDestroy(matchedPattern);
					FcCharSetDestroy(charSet);
					FcPatternDestroy(pattern);
					return GetFont(fontFamily, nullptr);
				}
				FcPatternDestroy(matchedPattern);
			}

			FcCharSetDestroy(charSet);
			FcPatternDestroy(pattern);
		}

		FcPattern* pattern = FcPatternCreate();
		FcCharSet* charSet = FcCharSetCreate();
		FcCharSetAddChar(charSet, codepoint);
		FcPatternAddCharSet(pattern, FC_CHARSET, charSet);
		FcPatternAddBool(pattern, FC_SCALABLE, FcTrue);

		FcResult result;
		FcPattern* matchedPattern = FcFontMatch(nullptr, pattern, &result);
		std::string fontFamily;

		if (matchedPattern != nullptr)
		{
			FcChar8* family = nullptr;
			if (FcPatternGetString(matchedPattern, FC_FAMILY, 0, &family) == FcResultMatch)
			{
				fontFamily = reinterpret_cast<const char*>(family);
			}
			FcPatternDestroy(matchedPattern);
		}

		FcCharSetDestroy(charSet);
		FcPatternDestroy(pattern);

		return GetFont(fontFamily, nullptr);
	}
}