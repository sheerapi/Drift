#pragma once
#include <string>
#include <vector>

namespace Drift
{
	struct ApplicationID
	{
	public:
		std::string Domain{"com"};
		std::string Org;
		std::string Name;

		ApplicationID(const std::string& appId);
		ApplicationID() = default;

		[[nodiscard]] auto GetCompoundID() const -> std::string;

		static auto CheckAppID(const std::string& appId) -> bool;
	};

	struct EnvironmentInfo
	{
	public:
		std::string WorkingDirectory;
		std::string ExecutablePath;
		std::string AssetsDirectory;
		std::string RootPath;
		std::vector<std::string> CommandLineArgs;
	};
}