#include "core/Application.h"
#include "core/Logger.h"

namespace Drift
{
    Application::Application(const std::string& appId)
    {
        if (main != nullptr)
        {
            dt_coreFatal("Another application instance is running!");
        }

        main = this;

        _id = ApplicationID(appId);
    }
}