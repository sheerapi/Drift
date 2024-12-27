#pragma once
#include "core/Element.h"
#include "core/SkFont.h"
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
	};
}