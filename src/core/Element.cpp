#include "core/Element.h"
#include "utils/Demangle.h"
#include "utils/StringUtils.h"

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
        std::string classString;
        for (size_t i = 0; i < _className.size(); i++)
        {
            auto cls = _className[i];
			classString += "." + cls + (i >= _className.size() - 1 ? "" : " ");
		}

        return getNamespaceFreeName(dt_type(*this)) + "[#" + _id + " " + classString + "]";
    }

	auto Element::ID(const std::string& newId) -> Element*
    {
        _id = newId;
        return this;
    }

	auto Element::ID() const -> std::string
    {
        return _id;
    }

	auto Element::ClassName(const std::string& classes) -> Element*
    {
        _className = stringSplit(classes, " ");
        return this;
    }

    auto Element::ClassName() const -> std::string
    {
        return join(_className, ' ');
    }

	void Element::DebugPrint(int depth)
    {
        std::string tabs;
        for (int i = 0; i < depth; i++)
        {
            tabs += "   ";
        }

        dt_coreDebug("{}{}", tabs, ToString());

        for (auto& child : Children)
        {
            child->DebugPrint(depth + 1);
        }
    }
}