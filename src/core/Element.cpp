#include "core/Element.h"
#include "utils/Demangle.h"

namespace Drift
{
    auto Element::AddChild(Element* element) -> std::shared_ptr<Element>
    {
		return AddChild(std::shared_ptr<Element>(element));
	}

	auto Element::AddChild(const std::shared_ptr<Element>& element) -> std::shared_ptr<Element>
	{
		if (element == nullptr)
		{
			dt_coreError("Tried to add a null child!");
			return nullptr;
		}

		element->_parent = this;
		Children.push_back(element);
		return element;
	}

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