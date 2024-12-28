#pragma once
#include "core/Element.h"
#include "core/FontManager.h"
#include "core/SkFont.h"
#include "modules/skshaper/include/SkShaper.h"
#include "yoga/YGNode.h"
#include <memory>
#include <string>

namespace Drift
{
	class dt_api Text : public Element
	{
	public:
		std::string Content;

		Text(const std::string& content = "");
		void Update() override;
		void Draw() override;

	private:
		SkFont _font;
		std::unique_ptr<SkShaper> _shaper{SkShaper::Make(FontManager::GetFontMgr())};

		static auto MeasureText(const YGNode* node, float width, YGMeasureMode widthMode,
								  float height, YGMeasureMode heightMode) -> YGSize;

		static auto BaselineText(const YGNode* node, float width, float height) -> float;
	};
}