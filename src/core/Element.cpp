#include "core/Element.h"
#include "utils/Demangle.h"
#include "utils/StringUtils.h"
#include "yoga/YGNode.h"
#include "yoga/YGNodeLayout.h"
#include "yoga/YGNodeStyle.h" // IWYU pragma: keep
#include <format>

namespace Drift
{
	Element::Element()
	{
		_ygNode = YGNodeNew();
		_bounds = std::make_shared<BoundingBox>();
	}

    Element::~Element()
    {
        YGNodeFree(_ygNode);
    }

	auto Element::AddChild(Element* element) -> std::shared_ptr<Element>
	{
		return AddChild(std::shared_ptr<Element>(element));
	}

	auto Element::AddChild(const std::shared_ptr<Element>& element)
		-> std::shared_ptr<Element>
	{
		if (element == nullptr)
		{
			dt_coreError("Tried to add a null child!");
			return nullptr;
		}

		element->_parent = this;
		Children.push_back(element);
        YGNodeInsertChild(_ygNode, element->_ygNode, YGNodeGetChildCount(_ygNode));
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

		return std::format("{} [#{} {} ({}x{} @ {},{})]",
							getNamespaceFreeName(dt_type(*this)), _id, classString,
							GetBoundingBox().Width, GetBoundingBox().Height,
							GetBoundingBox().X, GetBoundingBox().Y);
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

	void Element::Tick()
	{
		if (_enabled)
		{
			Update();
		}

		for (auto& child : Children)
		{
			child->Tick();
		}

		if (YGNodeGetHasNewLayout(_ygNode))
		{
			YGNodeSetHasNewLayout(_ygNode, false);
			YGNodeCalculateLayout(_ygNode, YGUndefined, YGUndefined, YGDirectionLTR);

			_bounds->X = GetAbsoluteX();
			_bounds->Y = GetAbsoluteY();
			_bounds->Width = YGNodeLayoutGetWidth(_ygNode);
			_bounds->Height = YGNodeLayoutGetHeight(_ygNode);
		}
	}

	void Element::Render()
	{
		if (_enabled)
		{
			Draw();

			for (auto& child : Children)
			{
				child->Render();
			}
		}
	}

    auto Element::GetBoundingBox() -> BoundingBox
    {
        return *_bounds;
    }

    auto Element::GetAbsoluteX() -> float
    {
        return YGNodeLayoutGetLeft(_ygNode) + (_parent != nullptr ? _parent->GetAbsoluteX() : 0);
    }

	auto Element::GetAbsoluteY() -> float
	{
		return YGNodeLayoutGetTop(_ygNode) +
			   (_parent != nullptr ? _parent->GetAbsoluteY() : 0);
	}

	void Element::ForceLayoutRefresh()
    {
		YGNodeSetHasNewLayout(_ygNode, false);
		YGNodeCalculateLayout(_ygNode, YGUndefined, YGUndefined, YGDirectionLTR);

		_bounds->X = GetAbsoluteX();
		_bounds->Y = GetAbsoluteY();
		_bounds->Width = YGNodeLayoutGetWidth(_ygNode);
		_bounds->Height = YGNodeLayoutGetHeight(_ygNode);

        for (auto& child : Children)
        {
            child->ForceLayoutRefresh();
        }
	}

		dt_yogaPropertyValueDef(Width);
	dt_yogaPropertyValueDef(Height);

	dt_yogaPropertyValueDef(MinWidth);
	dt_yogaPropertyValueDef(MinHeight);

	dt_yogaPropertyValueDef(MaxWidth);
	dt_yogaPropertyValueDef(MaxHeight);

	dt_yogaPropertyValueDef(FlexBasis);
	dt_yogaPropertySimpleDef(FlexGrow);
	dt_yogaPropertySimpleDef(FlexShrink);
	dt_yogaPropertySimpleDef(AspectRatio);

	dt_yogaPropertyEdgeDef(Margin);
	dt_yogaPropertyEdgeDef(Padding);
	dt_yogaPropertyEdgeNoValueDef(Border);
	dt_yogaPropertyEdgeDef(Position);

	dt_yogaPropertyEnumDef(AlignContent, enum AlignItems, YGAlign);
	dt_yogaPropertyEnumDef(AlignItems, enum AlignItems, YGAlign);
	dt_yogaPropertyEnumDef(JustifyContent, enum JustifyContent, YGJustify);
	dt_yogaPropertyEnumDef(Display, DisplayType, YGDisplay);
	dt_yogaPropertyEnumDef(Overflow, enum Overflow, YGOverflow);
	dt_yogaPropertyEnumDef(FlexWrap, enum Wrap, YGWrap);
	dt_yogaPropertyEnumDef(FlexDirection, enum FlexDirection, YGFlexDirection);
	dt_yogaPropertyEnumDef(PositionType, enum PositionType, YGPositionType);

	auto Element::NodeType(enum NodeType val) -> Element*
	{
		YGNodeSetNodeType(_ygNode, (YGNodeType)((int)val));
		return this;
	}
	auto Element::NodeType() -> enum NodeType
	{
		return (enum NodeType)((int)YGNodeGetNodeType(_ygNode));
	}

	auto Element::GapHorizontal(float val) -> Element*
	{
		YGNodeStyleSetGap(_ygNode, YGGutter::YGGutterRow, val);
		return this;
	}

	auto Element::GapHorizontal() -> float
	{
		return YGNodeStyleGetGap(_ygNode, YGGutter::YGGutterRow).value;
	}

	auto Element::GapVertical(float val) -> Element*
	{
		YGNodeStyleSetGap(_ygNode, YGGutter::YGGutterColumn, val);
		return this;
	}

	auto Element::GapVertical() -> float
	{
		return YGNodeStyleGetGap(_ygNode, YGGutter::YGGutterColumn).value;
	}

	auto Element::Gap(float val) -> Element*
	{
		YGNodeStyleSetGap(_ygNode, YGGutter::YGGutterAll, val);
		return this;
	}

	auto Element::Gap() -> float
	{
		return YGNodeStyleGetGap(_ygNode, YGGutter::YGGutterAll).value;
	}
}