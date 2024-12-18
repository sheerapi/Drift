#pragma once
#include "toml++/toml.hpp" // IWYU pragma: keep

namespace Drift
{
    class ConfigManager
    {
    public:
    private:
        inline static toml::table table;
    };
}