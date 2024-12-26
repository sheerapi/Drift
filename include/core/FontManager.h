#pragma once
#include "core/Macros.h"
#include "core/SkFontMgr.h"
#include "core/SkTypeface.h"
#include <fontconfig/fontconfig.h>
#include <string>
#include <unordered_map>
#include <vector>

namespace Drift
{
	class dt_api FontManager
	{
	public:
		static void Init();
		static auto HasFont(const std::string& name) -> bool;
		static auto ResolveFontStack(const std::vector<std::string>& stack)
			-> std::string;
		static auto GetFont(const std::string& name) -> SkTypeface*;
		static void Shutdown();

	private:
		inline static std::unordered_map<std::string, SkTypeface*> fonts;
		inline static sk_sp<SkFontMgr> fontMgr;
	};
}