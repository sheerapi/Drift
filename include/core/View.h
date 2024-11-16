#pragma once
#include "core/Element.h"
#include <memory>
#include <vector>

namespace Drift
{
    class View
    {
    public:
        virtual void Present() {};
        virtual void Update() {};
        virtual void Render() {};

        [[nodiscard]] inline auto IsEnabled() const -> bool
        {
            return _enabled;
        }

        inline void SetEnabled(bool enabled)
        {
            _enabled = enabled;
        }

        void PrintElementTree();

    protected:
		std::vector<std::shared_ptr<Element>> Children;

	private:
        bool _enabled{true};
    };
}