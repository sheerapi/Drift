#pragma once
#include <memory>
#include <vector>

namespace Drift
{
    class Element
    {
    public:
        Element();
        
    private:
        std::vector<std::shared_ptr<Element>> _children;
        std::weak_ptr<Element> _parent;
    };
}