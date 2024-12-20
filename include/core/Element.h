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
            return AddChild(std::make_shared<T>(args...));
        }

		template<typename T, typename... Args> auto AddStyle(Args&& ...args) -> Element*
		{
			typeCheck<Styling::StyleBase, T>();
			auto style = std::make_shared<T>(args...);

			if (!_styles.contains(style->StyleName()))
			{
				_styles[style->StyleName()] = style;

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
				(static_cast<T*>(_styles[style->StyleName()].get()))->EditStyle(args...);
			}

			return this;
		}

		template<typename T> auto HasStyle() -> bool
		{
			typeCheck<Styling::StyleBase, T>();
			auto style = std::make_shared<T>();
			return _styles.contains(style->StyleName());
		}

		template<typename T> auto GetStyle() -> std::shared_ptr<T>
		{
			typeCheck<Styling::StyleBase, T>();
			auto style = std::make_shared<T>();

			if (!_styles.contains(style->StyleName()))
			{
				dt_coreError("Tried to get a style that doesn't exist! (Style: {})", style->StyleName());
				return nullptr;
			}

			return std::static_pointer_cast<T>(_styles[style->StyleName()]);
		}

		auto ID(const std::string& newId) -> Element*;
		[[nodiscard]] auto ID() const -> std::string;

		auto Enabled(bool enabled) -> Element*;
		[[nodiscard]] auto Enabled() const -> bool;

		auto ClassName(const std::string& classes) -> Element*;
		[[nodiscard]] auto ClassName() const -> std::string;

		auto AddChild(Element* element) -> std::shared_ptr<Element>;
		auto AddChild(const std::shared_ptr<Element>& element) -> std::shared_ptr<Element>;

		auto GetBoundingBox() -> BoundingBox;

		// actually these would still be relative to the containing view but wtv
		auto GetAbsoluteX() -> float;
		auto GetAbsoluteY() -> float;

		[[nodiscard]] auto GetPercentWidth(float percent) -> float;
		[[nodiscard]] auto GetPercentHeight(float percent) -> float;

		void Tick();
		void Render();

		void ForceLayoutRefresh();

		virtual auto ToString() -> std::string;
		void DebugPrint(int depth = 0);

		auto WidthPercent(float val) -> Element*;
		auto HeightPercent(float val) -> Element*;
		auto FlexBasisPercent(float val) -> Element*;

		auto ZIndex(int val) -> Element*;
		auto ZIndex() const -> int;

		auto ChildAt(int index) -> std::shared_ptr<Element>;

		auto GetLayoutEngineHandle() -> void*;

		auto ReceivesInput(bool receives) -> Element*;
		auto ReceivesInput() const -> bool;

		static auto FindDeepestMatch(Element* object, Vector2 pos) -> Element*;

		dt_yogaPropertySimple(Width);
		dt_yogaPropertySimple(Height);

		dt_yogaPropertySimple(MinWidth);
		dt_yogaPropertySimple(MinHeight);

		dt_yogaPropertySimple(MaxWidth);
		dt_yogaPropertySimple(MaxHeight);

		dt_yogaPropertySimple(FlexBasis);
		dt_yogaPropertySimple(FlexGrow);
		dt_yogaPropertySimple(FlexShrink);
		dt_yogaPropertySimple(AspectRatio);

		dt_yogaPropertySimple(GapHorizontal);
		dt_yogaPropertySimple(GapVertical);
		dt_yogaPropertySimple(Gap);

		dt_yogaPropertyType(AlignContent, AlignItems);
		dt_yogaPropertyType(AlignItems, enum AlignItems);
		dt_yogaPropertyType(JustifyContent, enum JustifyContent);
		dt_yogaPropertyType(Display, DisplayType);
		dt_yogaPropertyType(Overflow, enum Overflow);
		dt_yogaPropertyType(FlexWrap, enum Wrap);
		dt_yogaPropertyType(FlexDirection, enum FlexDirection);
		dt_yogaPropertyType(PositionType, enum PositionType);
		dt_yogaPropertyType(NodeType, enum NodeType);
		dt_yogaPropertyType(BoxSizing, enum BoxSizing);

		dt_yogaPropertyEdge(Margin);
		dt_yogaPropertyEdge(Padding);
		dt_yogaPropertyEdge(Border);
		dt_yogaPropertyEdge(Position);

		void On(std::string signal, const EventHandler& handler);
		void Remove(std::string signal);
		void Remove(std::string signal, EventHandler& handler);

		auto GetContainingActivity() -> Activity*;
		void SetContainingActivity(Activity* activity);

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

		void _refreshLayout(bool force = false);
		void _refreshState(const std::string& eventName);

		std::unordered_map<std::string, std::vector<EventHandler>> _handlers;
		std::unordered_map<std::string, std::shared_ptr<Styling::StyleBase>> _styles;

		template <typename T, typename... Args> auto _addStyleIfNotFound(Args&&... args) -> Element*
		{
			typeCheck<Styling::StyleBase, T>();
			auto style = std::make_shared<T>(args...);

			if (!_styles.contains(style->StyleName()))
			{
				_styles[style->StyleName()] = style;

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

#ifdef DEBUG
		[[nodiscard]] auto _getPaint() const -> unsigned int;
#endif
	};
}