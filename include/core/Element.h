#pragma once
#include "../utils/Demangle.h"
#include "../core/Macros.h"
#include "core/LayoutEnums.h"
#include "styles/Style.h"
#include "utils/BoundingBox.h"
#include "utils/Vector2.h"
#include "yoga/YGConfig.h"
#include <memory>
#include <vector>

namespace Drift
{
	class Activity;

	struct Scrollable
	{
	public:
		float ScrollOffsetX{0};
		float ScrollOffsetY{0};
		float TargetScrollOffsetX{0};
		float TargetScrollOffsetY{0};

		float ScrollMagnitude{30};
	};

	struct dt_api Event
	{
	public:
		void* Data{nullptr};

		inline void StopPropagation()
		{
			_propagate = false;
		}

		Event(void* data) : Data(data) {};

	private:
		bool _propagate{true};
		friend class Element;
	};

	using EventHandler = std::function<void(Event)>;
	
	struct dt_api ElementStates
	{
	public:
		bool Enabled{true};
		bool Hovered{false};
		bool Focused{false};
		bool Clicked{false};
	};

	class dt_api Element
	{
	public:
		Element();
		virtual ~Element();

        template<typename T, typename... Args> auto AddChild(Args&& ...args) -> std::shared_ptr<T>
        {
            typeCheck<Element, T>();
            return std::dynamic_pointer_cast<T>(AddChild(std::make_shared<T>(args...)));
        }

		template<typename T, typename... Args> auto AddStyle(Args&& ...args) -> Element*
		{
			typeCheck<Styling::StyleBase, T>();
			auto style = std::make_shared<T>();

			if (!_styleKeys.contains(style->StyleName()))
			{
				_styleKeys[style->StyleName()] = style;
				_styles.push_back(style);
				(static_cast<T*>(_styleKeys[style->StyleName()].get()))
					->EditStyle(this, args...);

				std::sort(_styles.begin(), _styles.end(), [](const auto& a, const auto& b)
						  { return a->StylePriority() > b->StylePriority(); });

				if (style->IsInheritable())
				{
					for (auto& child : Children)
					{
						child->_addStyleIfNotFound<T>(args...);
					}
				}
			}
			else
			{
				(static_cast<T*>(_styleKeys[style->StyleName()].get()))->EditStyle(this, args...);
			}

			return this;
		}

		template<typename T> auto HasStyle() -> bool
		{
			typeCheck<Styling::StyleBase, T>();
			auto style = std::make_shared<T>();
			return _styleKeys.contains(style->StyleName());
		}

		template<typename T> auto GetStyle() -> std::shared_ptr<T>
		{
			typeCheck<Styling::StyleBase, T>();
			auto style = std::make_shared<T>();

			if (!_styleKeys.contains(style->StyleName()))
			{
				dt_coreError("Tried to get a style that doesn't exist! (Style: {})", style->StyleName());
				return {};
			}

			return std::static_pointer_cast<T>(_styleKeys[style->StyleName()]);
		}

		auto ID(const std::string& newId) -> Element*;
		[[nodiscard]] auto ID() const -> std::string;

		auto Enabled(bool enabled) -> Element*;
		[[nodiscard]] auto Enabled() const -> bool;

		auto ClassName(const std::string& classes) -> Element*;
		[[nodiscard]] auto ClassName() const -> std::string;

		auto HasClassName(const std::string& name) -> bool;
		auto AddClassName(const std::string& name) -> Element*;
		auto RemoveClassName(const std::string& name) -> Element*;

		auto AddChild(Element* element) -> std::shared_ptr<Element>;
		auto AddChild(const std::shared_ptr<Element>& element) -> std::shared_ptr<Element>;

		auto GetBoundingBox() -> BoundingBox;

		// actually these would still be relative to the containing view but wtv
		auto GetAbsoluteX() -> float;
		auto GetAbsoluteY() -> float;

		[[nodiscard]] auto GetPercentWidth(float percent) -> float;
		[[nodiscard]] auto GetPercentHeight(float percent) -> float;

		[[nodiscard]] auto GetPercentWidthInverse(float pixels) -> float;
		[[nodiscard]] auto GetPercentHeightInverse(float pixels) -> float;

		void Tick();
		void Render();

		void ForceLayoutRefresh();

		virtual auto ToString() -> std::string;
		void DebugPrint(int depth = 0);

		auto ZIndex(int val) -> Element*;
		auto ZIndex() const -> int;

		auto ChildAt(int index) -> std::shared_ptr<Element>;

		auto GetLayoutEngineHandle() -> void*;

		auto ReceivesInput(bool receives) -> Element*;
		auto ReceivesInput() const -> bool;

		auto GetContentWidth() -> float;
		auto GetContentHeight() -> float;

		static auto FindDeepestMatch(Element* object, Vector2 pos) -> Element*;

		dt_yogaPropertySimple(Width);
		dt_yogaPropertySimple(Height);

		dt_yogaPropertySimple(MinWidth);
		dt_yogaPropertySimple(MinHeight);

		dt_yogaPropertySimple(MaxWidth);
		dt_yogaPropertySimple(MaxHeight);

		dt_yogaPropertySimple(FlexBasis);
		dt_yogaPropertySimpleNoValue(FlexGrow);
		dt_yogaPropertySimpleNoValue(FlexShrink);
		dt_yogaPropertySimpleNoValue(AspectRatio);

		dt_yogaPropertySimple(GapHorizontal);
		dt_yogaPropertySimple(GapVertical);
		dt_yogaPropertySimple(Gap);

		dt_yogaPropertyType(AlignContent, Align);
		dt_yogaPropertyType(AlignItems, Align);
		dt_yogaPropertyType(JustifyContent, Justify);
		dt_yogaPropertyType(Display, DisplayType);
		dt_yogaPropertyType(Overflow, OverflowType);
		dt_yogaPropertyType(FlexWrap, WrapType);
		dt_yogaPropertyType(FlexDirection, Direction);
		dt_yogaPropertyType(PositionType, enum PositionType);
		dt_yogaPropertyType(NodeType, enum NodeType);
		dt_yogaPropertyType(BoxSizing, BoxSizingType);

		dt_yogaPropertyEdge(Margin);
		dt_yogaPropertyEdge(Padding);
		dt_yogaPropertyEdge(Border);
		dt_yogaPropertyEdge(Position);
		dt_yogaPropertyEdge(BorderRadius);

		void On(std::string signal, const EventHandler& handler);
		void Remove(std::string signal);
		void Remove(std::string signal, EventHandler& handler);

		auto GetContainingActivity() -> Activity*;
		void SetContainingActivity(Activity* activity);

		auto GetScrollOffsetX() const -> float;
		auto GetScrollOffsetY() const -> float;

		auto Focus(bool focus = true) -> Element*;
		auto Focusable() const -> bool;

		auto IsOrphan() const -> bool;
		auto GetParent() -> Element*;

		inline void RemoveAll()
		{
			_handlers.clear();
		}

		void EmitSignal(std::string signal, Event event = {nullptr});

	protected:
		std::vector<std::shared_ptr<Element>> Children;
		virtual void Update() {};
		virtual void Draw();

		virtual void BeginDraw();
		virtual void EndDraw();

		virtual void BeginUpdate() {};
		virtual void EndUpdate() {};

	private:
		YGNodeRef _ygNode;
		Element* _parent{nullptr};
		Activity* _activity{nullptr};
		bool _focusable{true};
		bool _receivesInput{true};
		bool _zOrderingChanged{true};
		int _zIndex;
		ElementStates _states;
        std::string _id;
        std::vector<std::string> _className;
		Scrollable _scrollable;

		void _refreshLayout(bool force = false);
		void _refreshState(const std::string& eventName);
		void _scroll(Vector2 delta);

		std::unordered_map<std::string, std::vector<EventHandler>> _handlers;
		std::unordered_map<std::string, std::shared_ptr<Styling::StyleBase>> _styleKeys;
		std::vector<std::shared_ptr<Styling::StyleBase>> _styles;

		template <typename T, typename... Args> auto _addStyleIfNotFound(Args&&... args) -> Element*
		{
			typeCheck<Styling::StyleBase, T>();
			auto style = std::make_shared<T>();

			if (!_styleKeys.contains(style->StyleName()))
			{
				_styleKeys[style->StyleName()] = style;
				_styles.push_back(style);
				(static_cast<T*>(_styleKeys[style->StyleName()].get()))
					->EditStyle(this, args...);

				std::sort(_styles.begin(), _styles.end(), [](const auto& a, const auto& b)
						  { return a->StylePriority() > b->StylePriority(); });

				if (style->IsInheritable())
				{
					for (auto& child : Children)
					{
						child->_addStyleIfNotFound<T>(args...);
					}
				}
			}

			return this;
		}

		void _addExistingStyle(const std::shared_ptr<Styling::StyleBase>& style);

#ifdef DEBUG
		[[nodiscard]] auto _getPaint() const -> unsigned int;
#endif
	};
}