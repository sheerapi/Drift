#pragma once
#include "utils/Demangle.h"
#include "core/Macros.h"
#include <memory>
#include <vector>

namespace Drift
{
	class dt_api Element
	{
	public:
		Element() = default;

        template<typename T, typename... Args> auto AddChild(Args&& ...args) -> std::shared_ptr<T>
        {
            typeCheck<Element, T>();
            return AddChild(std::make_shared<T>(args...));
        }

        auto AddChild(Element* element) -> std::shared_ptr<Element>;
		auto AddChild(const std::shared_ptr<Element>& element) -> std::shared_ptr<Element>;

		virtual auto ToString() -> std::string;
		void DebugPrint(int depth = 0);

		virtual void Update() {};
		virtual void Draw() {};

	protected:
		std::vector<std::shared_ptr<Element>> Children;

	private:
		Element* _parent;
        std::string _id;
        std::vector<std::string> _className;
	};
}