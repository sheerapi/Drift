#pragma once
#include "core/Macros.h"
#include "styles/Style.h"

namespace Drift
{
    struct dt_api BoundingBoxV
    {
    public:
        Styling::Value Width;
		Styling::Value Height;
		Styling::Value X;
		Styling::Value Y;
	};
}