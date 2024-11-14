#pragma once
#include <string>

namespace Drift
{
    struct ApplicationID
	{
	public:
		std::string Domain{"com"};
		std::string Organization;
		std::string Name;
	};

    class Application
    {
    public:
        inline static Application* main{nullptr};

        Application(const std::string& appId);
        void Present();

    private:
        ApplicationID _id;
    };
}