#include "core/Element.h"
#include "utils/Demangle.h"

namespace Drift
{
	auto Element::ToString() -> std::string
    {
        return getNamespaceFreeName(dt_type(*this));
    }

	void Element::DebugPrint(int depth)
    {
        std::string tabs;
        for (int i = 0; i < depth; i++)
        {
            tabs += "   ";
        }

        dt_coreInfo("{}{}", tabs, ToString());

        for (auto& child : Children)
        {
            child->DebugPrint(depth + 1);
        }
    }
}