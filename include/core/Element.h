#pragma once
#include <memory>
#include <vector>

namespace Drift
{
	class Element
	{
	public:
		Element();

		virtual auto ToString() -> std::string;
		void DebugPrint(int depth = 0);

	protected:
		std::vector<std::shared_ptr<Element>> Children;

	private:
		std::weak_ptr<Element> _parent;
	};
}