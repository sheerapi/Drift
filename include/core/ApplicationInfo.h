#pragma once
#include "core/Macros.h"
#include <string>
#include <vector>

namespace Drift
{
	struct dt_api ApplicationID
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

	struct dt_api EnvironmentInfo
	{
	public:
		std::string WorkingDirectory;
		std::string ExecutablePath;
		std::string AssetsDirectory;
		std::string RootPath;
		std::vector<std::string> CommandLineArgs;
		bool Verbose{false};

		EnvironmentInfo();

		auto HasFlag(const std::string& flag) -> bool;
	};
}