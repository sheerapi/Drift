#pragma once
#include "../utils/Demangle.h"
#include "../core/Macros.h"
#include "core/LayoutEnums.h"
#include "utils/BoundingBox.h"
#include "yoga/YGConfig.h"
#include <memory>
#include <vector>

namespace Drift
{
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

		auto GetLayoutEngineHandle() -> void*;

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

	protected:
		std::vector<std::shared_ptr<Element>> Children;
		virtual void Update() {};
		virtual void Draw();

	private:
		YGNodeRef _ygNode;
		Element* _parent{nullptr};
		bool _enabled{true};
        std::string _id;
        std::vector<std::string> _className;

		void _refreshLayout(bool force = false);
	};
}