#include "core/Element.h"
#include "core/Logger.h"
#include "core/SkColor.h"
#include "core/SkPaint.h"
#include "core/SkRect.h"
#include "events/InputSystem.h"
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
		auto* config = YGConfigNew();
		YGConfigSetPointScaleFactor(config, 1.0);

		_ygNode = YGNodeNewWithConfig(config);
		Overflow(Overflow::Visible);
		FlexShrink(0);
		PositionType(PositionType::Static);
		FlexDirection(FlexDirection::Row);
		AlignContent(AlignItems::Stretch);

		On("hover", [this](Event data) { _refreshState("hover"); });
		On("unhover", [this](Event data) { _refreshState("unhover"); });
		On("focus", [this](Event data) { _refreshState("focus"); });
		On("unfocus", [this](Event data) { _refreshState("unfocus"); });

		On("click", [this](Event data) { _refreshState("click"); });
		On("unclick", [this](Event data) { _refreshState("unclick"); });
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

		std::sort(Children.begin(), Children.end(),
				  [](const auto& a, const auto& b) { return a->_zIndex < b->_zIndex; });

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

	}

	void Element::BeginDraw()
	{
		
	}

	void Element::EndDraw()
	{
		
	}

	auto Element::Focus(bool focus) -> Element*
	{
		Input::Focus(this, focus);

		return this;
	}

	auto Element::Focusable() const -> bool
	{
		return _focusable;
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
		if (_states.Enabled)
		{
			BeginUpdate();

			Update();

			for (auto& child : Children)
			{
				child->Tick();
			}

			EndUpdate();
		}

		if (_zOrderingChanged)
		{
			std::sort(Children.begin(), Children.end(),
					  [](const auto& a, const auto& b) { return a->_zIndex < b->_zIndex; });

			_zOrderingChanged = false;
		}

		for (auto& style : _styles)
		{
			if (style.second->IsDirty())
			{
				style.second->RecalculateLayout(this);
			}
		}

		if (_parent == nullptr)
		{
			_refreshLayout();
		}
	}

	void Element::Render()
	{
		if (_states.Enabled)
		{
			for (auto& style : _styles)
			{
				style.second->BeginDrawStyle(this, dt_renderContext->Canvas);
			}

			BeginDraw();
			Draw();

			for (auto& child : Children)
			{
				child->Render();
			}

			EndDraw();

			for (auto& style : _styles)
			{
				style.second->EndDrawStyle(this, dt_renderContext->Canvas);
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

	auto Element::FlexBasisPercent(float val) -> Element*
	{
		if (_parent == nullptr)
		{
			dt_coreWarn("Element is orphaned! Percent requires a parent");
			return this;
		}

		YGNodeStyleSetFlexBasisPercent(_ygNode, val);
		return this;
	}

	auto Element::FindDeepestMatch(Element* object, Vector2 pos) -> Element*
	{
		auto bounds = object->GetBoundingBox();

		if (!SkRect::Intersects(
				SkRect::MakeXYWH(bounds.X, bounds.Y, bounds.Width, bounds.Height),
				SkRect::MakeXYWH(pos.X, pos.Y, 1, 1)))
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

	auto Element::ReceivesInput(bool receives) -> Element*
	{
		_receivesInput = receives;
		return this;
	}

	auto Element::ReceivesInput() const -> bool
	{
		return _receivesInput;
	}

	auto Element::ChildAt(int index) -> std::shared_ptr<Element>
	{
		if (index <= 0 || index >= Children.size())
		{
			dt_coreError("Tried to access a child out of bounds! (Expected 0 < index < "
						 "{}, index = {})",
						 Children.size(), index);
						
			return nullptr;
		}

		return Children[index];
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

#ifdef DEBUG
	auto Element::_getPaint() const -> unsigned int
	{
		if (_states.Focused)
		{
			return SK_ColorMAGENTA;
		}

		if (_states.Clicked)
		{
			return SK_ColorBLUE;
		}

		if (_states.Hovered)
		{
			return SK_ColorRED;
		}

		return Children.size() == 0 ? SK_ColorWHITE : SK_ColorTRANSPARENT;
	}
#endif

	void Element::_refreshState(const std::string& eventName)
	{
		if (!_receivesInput || !_states.Enabled)
		{
			return;
		}

		// yandere dev moment
		// why doesnt c++ have string switches ffs
		if (eventName == "hover")
		{
			_states.Hovered = true;
		}

		if (eventName == "unhover")
		{
			_states.Hovered = false;
		}

		if (eventName == "focus")
		{
			_states.Focused = true;
		}

		if (eventName == "unfocus")
		{
			_states.Focused = false;
		}

		if (eventName == "click")
		{
			_states.Clicked = true;
		}

		if (eventName == "unclick")
		{
			_states.Clicked = false;
		}
	}

	void Element::On(std::string signal, const EventHandler& handler)
	{
		_handlers[stringToLower(std::move(signal))].push_back(handler);
	}

	void Element::Remove(std::string signal)
	{
		signal = stringToLower(std::move(signal));

		if (!_handlers.contains(signal))
		{
			dt_coreWarn("Tried to remove handlers of signal \"{}\", but no handlers "
						"of that signal could be found",
						signal);

			return;
		}

		_handlers[signal].clear();
	}

	void Element::Remove(std::string signal, EventHandler& handler)
	{
		signal = stringToLower(std::move(signal));

		if (!_handlers.contains(signal))
		{
			dt_coreWarn("Tried to remove a handler of signal \"{}\", but no handlers "
						"of that signal could be found",
						signal);

			return;
		}

		_handlers[signal].erase(std::remove_if(_handlers[signal].begin(),
											   _handlers[signal].end(),
											   [=](auto itr) { return itr = handler; }),
								_handlers[signal].end());
	}

	void Element::EmitSignal(std::string signal, Event event)
	{
		signal = stringToLower(signal);

		if (!_handlers.contains(signal))
		{
			if (event._propagate)
			{
				if (_parent != nullptr)
				{
					_parent->EmitSignal(signal, event);
				}
			}
			return;
		}

		for (const auto& handler : _handlers[signal])
		{
			try
			{
				handler(event);
			}
			catch (const std::exception& e)
			{
				dt_coreError("Exception ocurred while handling signal \"{}\": {}", signal,
							 e.what());
			}
			catch (...)
			{
				dt_coreFatal("An unknown exception ocurred while handling signal "
							 "\"{}\" that will be re-throwed.");
				throw "Unknown";
			}

			// just to be sure lol
		}

		if (event._propagate)
		{
			if (_parent != nullptr)
			{
				_parent->EmitSignal(signal, event);
			}
		}
	}

	auto Element::ZIndex(int val) -> Element*
	{
		_zIndex = val;
		if (_parent != nullptr)
		{
			_parent->_zOrderingChanged = true;
		}
		return this;
	}

	auto Element::ZIndex() const -> int
	{
		return _zIndex;
	}

	auto Element::GetContainingActivity() -> Activity*
	{
		return _activity;
	}

	void Element::SetContainingActivity(Activity* activity)
	{
		_activity = activity;

		for (auto& child : Children)
		{
			child->SetContainingActivity(activity);
		}
	}

	auto Element::IsOrphan() const -> bool
	{
		return _parent != nullptr;
	}

	auto Element::GetParent() -> Element*
	{
		return _parent;
	}
}