#pragma once
#include "core/Element.h"
#include <string>
#include <utility>

namespace Drift
{
	class dt_api Text : public Element
	{
	public:
		std::string Content;

		Text(std::string content = "") : Content(std::move(content)) {};

		void Draw() override;
	};
}