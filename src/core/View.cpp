#include "core/View.h"
#include "utils/Demangle.h"

namespace Drift
{
	void View::PrintElementTree()
	{
		dt_coreInfo("   {} [enabled = {}]", getNamespaceFreeName(dt_type(*this)), _enabled);

		for (auto& child : Children)
		{
			child->DebugPrint(2);
		}
	}
}