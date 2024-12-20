#include "utils/ConfigManager.h"
#include "core/Application.h"
#include "utils/PerformanceTimer.h"
#include <filesystem>
#include <fstream>

namespace Drift
{
	void ConfigManager::Init()
	{
		dt_stopwatch();

		auto driftPath =
			std::filesystem::path(Application::GetEnvironmentInfo().HomeDirectory) / ".config" / "drift";

		if (!std::filesystem::exists(driftPath))
		{
			dt_coreWarn("Drift directory does not exist! Creating it now...");
			std::filesystem::create_directories(driftPath);
		}

		if (std::filesystem::exists(driftPath / "config.toml"))
		{
			appTable = toml::parse_file((driftPath / "config.toml").string());
		}
		else
		{
			dt_coreWarn("No global configuration file found");
		}

		auto appPath =
			std::filesystem::path(Application::GetEnvironmentInfo().ApplicationDirectory);

		if (!std::filesystem::exists(appPath))
		{
			dt_warn("Application directory does not exist! Creating it now...");
			std::filesystem::create_directories(appPath);
		}

		if (std::filesystem::exists(appPath / "config.toml"))
		{
			appTable = toml::parse_file((appPath / "config.toml").string());
		}
		else
		{
			dt_warn("No application configuration file found");
		}
	}

	void ConfigManager::Write()
	{
		std::ofstream file(
			std::filesystem::path(Application::GetEnvironmentInfo().ApplicationDirectory) / "config.toml");

		file << appTable;
		file.close();
	}
}