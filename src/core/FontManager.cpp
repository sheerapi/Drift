#include "core/FontManager.h"
#include "core/Application.h" // IWYU pragma: keep
#include "core/Logger.h"
#include "core/SkFontMgr.h"
#include "fontconfig/fontconfig.h"
#include "ports/SkFontMgr_fontconfig.h"
#include "utils/ConfigManager.h"
#include "utils/PerformanceTimer.h"

namespace Drift
{
	void FontManager::Init()
	{
		dt_stopwatch();

		config = FcInitLoadConfigAndFonts();

		if (config == nullptr)
		{
			dt_coreFatal("Failed to initialize FontConfig!");
		}

		fontMgr = SkFontMgr_New_FontConfig(config);

		dt_coreVerbose("Initialized FontConfig {}", FcGetVersion());

		fonts["sans-serif"] = GetFont(
			ResolveFontStack({ConfigManager::HasGlobalValue("fonts.sans_serif")
								  ? ConfigManager::GetGlobalString("fonts.sans_serif")
								  : "Inter",
							  "sans"}));

		fonts["serif"] =
			GetFont(ResolveFontStack({ConfigManager::HasGlobalValue("fonts.serif")
										  ? ConfigManager::GetGlobalString("fonts.serif")
										  : "Playfair Display",
									  "serif"}));

		fonts["monospaced"] =
			GetFont(ResolveFontStack({ConfigManager::HasGlobalValue("fonts.serif")
										  ? ConfigManager::GetGlobalString("fonts.serif")
										  : "Roboto Mono",
									  "monospaced"}));

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

	auto FontManager::GetFont(const std::string& name) -> SkTypeface*
	{
		if (fonts.contains(name))
		{
			return fonts[name];
		}

		if (!HasFont(name))
		{
			dt_coreError("Font {} was not found in the system!", name);
			return SkTypeface::MakeEmpty().get();
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
			fontMgr->makeFromFile(reinterpret_cast<char*>(filePath)).get();

		FcPatternDestroy(pattern);

		dt_coreVerbose("Loaded font {}", reinterpret_cast<char*>(family));
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
}