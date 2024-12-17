#include "core/Element.h"
#include "core/Logger.h"
#include "core/SkColor.h"
#include "core/SkPaint.h"
#include "core/SkRect.h"
#include "graphics/RendererContext.h"
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
		Overflow(Overflow::Visible);
		FlexShrink(0);
		PositionType(PositionType::Static);
		FlexDirection(FlexDirection::Row);
		AlignContent(AlignItems::Stretch);
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
		auto bounds = GetBoundingBox();

		std::string classString;
		for (size_t i = 0; i < _className.size(); i++)
		{
			auto cls = _className[i];
			classString += "." + cls + (i >= _className.size() - 1 ? "" : " ");
		}

		return std::format("{} [#{} {} ({}x{} @ {},{})]",
						   getNamespaceFreeName(dt_type(*this)), _id, classString,
						   bounds.Width, bounds.Height, bounds.X, bounds.Y);
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

	void Element::Draw()
	{
		if (_parent != nullptr)
		{
			auto bounds = GetBoundingBox();
			// dt_info("{} {} {} {}", bounds.X, bounds.Y, bounds.Width, bounds.Height);

			SkPaint paint;
			paint.setColor(Children.size() == 0 ? SK_ColorRED : SK_ColorWHITE);
			paint.setAntiAlias(true);

			SkPaint outline;
			outline.setColor(SK_ColorBLACK);
			outline.setAntiAlias(true);

			dt_canvas->drawRect(SkRect::MakeXYWH(bounds.X - 1, bounds.Y - 1,
												 bounds.Width + 2, bounds.Height + 2),
								outline);

			dt_canvas->drawRect(
				SkRect::MakeXYWH(bounds.X, bounds.Y, bounds.Width, bounds.Height), paint);
		}
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

		if (_parent == nullptr)
		{
			_refreshLayout();
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
		return {YGNodeLayoutGetWidth(_ygNode), YGNodeLayoutGetHeight(_ygNode),
				GetAbsoluteX(), GetAbsoluteY()};
	}

	auto Element::GetAbsoluteX() -> float
	{
		return YGNodeLayoutGetLeft(_ygNode) +
			   (_parent != nullptr ? _parent->GetAbsoluteX() : 0);
	}

	auto Element::GetAbsoluteY() -> float
	{
		return YGNodeLayoutGetTop(_ygNode) +
			   (_parent != nullptr ? _parent->GetAbsoluteY() : 0);
	}

	void Element::ForceLayoutRefresh()
	{
		_refreshLayout(true);
	}

	void Element::_refreshLayout(bool force)
	{
		if (YGNodeGetHasNewLayout(_ygNode) || force)
		{
			if (_parent == nullptr)
			{
				YGNodeSetHasNewLayout(_ygNode, false);
				YGNodeCalculateLayout(_ygNode, YGUndefined, YGUndefined, YGDirectionLTR);
			}
			else
			{
				_parent->_refreshLayout(force);
			}
		}
	}

	auto Element::GetLayoutEngineHandle() -> void*
	{
		return (void*)_ygNode;
	}

	auto Element::GetPercentWidth(float percent) -> float
	{
		_refreshLayout(); // We need to refresh the layout to get the latest bounds

		return GetBoundingBox().Width * (percent / 100);
	}

	auto Element::GetPercentHeight(float percent) -> float
	{
		_refreshLayout();

		return GetBoundingBox().Height * (percent / 100);
	}

	auto Element::WidthPercent(float val) -> Element*
	{
		if (_parent == nullptr)
		{
			dt_coreWarn("Element is orphaned! Percent requires a parent");
			return this;
		}

		YGNodeStyleSetWidthPercent(_ygNode, val);
		return this;
	}

	auto Element::HeightPercent(float val) -> Element*
	{
		if (_parent == nullptr)
		{
			dt_coreWarn("Element is orphaned! Percent requires a parent");
			return this;
		}

		YGNodeStyleSetHeightPercent(_ygNode, val);
		return this;
	}

	auto Element::FindDeepestMatch(Element *object, Vector2 pos) -> Element*
	{
		auto bounds = object->GetBoundingBox();

		if (!SkRect::Intersects(SkRect::MakeXYWH(bounds.X, bounds.Y, bounds.Width, bounds.Height), SkRect::MakeXYWH(pos.X, pos.Y, 1, 1)))
		{
			return nullptr;
		}

		for (auto itr = object->Children.rbegin(); itr < object->Children.rend(); ++itr)
		{
			auto* hit = FindDeepestMatch((*itr).get(), pos);			
			if (hit != nullptr)
			{
				return hit;
			}
		}

		return object;
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
	dt_yogaPropertyEnumDef(BoxSizing, enum BoxSizing, YGBoxSizing);

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