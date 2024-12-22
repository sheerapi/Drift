#include "utils/ConfigManager.h"
#include "core/Application.h"
#include "utils/PerformanceTimer.h"
#include <filesystem>
#include <fstream>
#include <utility>

namespace Drift
{
	void ConfigManager::Init()
	{
		dt_stopwatch();

		auto driftPath =
			std::filesystem::path(Application::GetEnvironmentInfo().HomeDirectory) /
			".config" / "drift";

		if (!std::filesystem::exists(driftPath))
		{
			dt_error("Drift directory does not exist! Creating it now...");
			std::filesystem::create_directories(driftPath);
		}

		if (std::filesystem::exists(driftPath / "config.toml"))
		{
			globalTable = toml::parse_file((driftPath / "config.toml").string());
		}
		else
		{
			dt_error("No global configuration file found");
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
		std::ofstream file(std::filesystem::path(
							   Application::GetEnvironmentInfo().ApplicationDirectory) /
						   "config.toml");

		file << appTable;
		file.close();
	}

	auto ConfigManager::GetInteger(const std::string& name) -> long
	{
		if (HasValue(name) && appTable.at_path(name).is_integer())
		{
			return appTable.at_path(name).as_integer()->get();
		}

		dt_error("Value at {} is either not found or does not match type (long)", name);
		return 0;
	}

	auto ConfigManager::GetDouble(const std::string& name) -> double
	{
		if (HasValue(name) && appTable.at_path(name).is_floating_point())
		{
			return appTable.at_path(name).as_floating_point()->get();
		}

		dt_error("Value at {} is either not found or does not match type (double)", name);
		return 0;
	}

	auto ConfigManager::GetString(const std::string& name) -> std::string
	{
		if (HasValue(name) && appTable.at_path(name).is_string())
		{
			return appTable.at_path(name).as_string()->get();
		}

		dt_error("Value at {} is either not found or does not match type (string)", name);
		return "";
	}

	auto ConfigManager::GetBoolean(const std::string& name) -> bool
	{
		if (HasValue(name) && appTable.at_path(name).is_boolean())
		{
			return appTable.at_path(name).as_boolean()->get();
		}

		dt_error("Value at {} is either not found or does not match type (bool)", name);
		return false;
	}

	auto ConfigManager::GetTable(const std::string& name) -> toml::table
	{
		if (HasValue(name) && appTable.at_path(name).is_table())
		{
			return *(appTable.at_path(name).as_table());
		}

		dt_error("Value at {} is either not found or does not match type (table)", name);
		return {};
	}

	auto ConfigManager::GetArray(const std::string& name) -> toml::array
	{
		if (HasValue(name) && appTable.at_path(name).is_array())
		{
			return *(appTable.at_path(name).as_array());
		}

		dt_error("Value at {} is either not found or does not match type (array)", name);
		return {};
	}

	auto ConfigManager::GetRootTable() -> toml::table
	{
		return appTable;
	}

	void ConfigManager::SetInteger(const std::string& name, long val)
	{
		Insert(name, val);
	}

	void ConfigManager::SetDouble(const std::string& name, double val)
	{
		Insert(name, val);
	}

	void ConfigManager::SetString(const std::string& name, const std::string& val)
	{
		Insert(name, val);
	}

	void ConfigManager::SetBoolean(const std::string& name, bool val)
	{
		Insert(name, val);
	}

	void ConfigManager::SetArray(const std::string& name, toml::array val)
	{
		Insert(name, std::move(val));
	}

	void ConfigManager::SetTable(const std::string& name, toml::table val)
	{
		Insert(name, std::move(val));
	}

	auto ConfigManager::GetGlobalInteger(const std::string& name) -> long
	{
		if (HasGlobalValue(name) && globalTable.at_path(name).is_integer())
		{
			return globalTable.at_path(name).as_integer()->get();
		}

		dt_error("Value at {} is either not found or does not match type (long)", name);
		return 0;
	}

	auto ConfigManager::GetGlobalDouble(const std::string& name) -> double
	{
		if (HasGlobalValue(name) && globalTable.at_path(name).is_floating_point())
		{
			return globalTable.at_path(name).as_floating_point()->get();
		}

		dt_error("Value at {} is either not found or does not match type (double)", name);
		return 0;
	}

	auto ConfigManager::GetGlobalString(const std::string& name) -> std::string
	{
		if (HasGlobalValue(name) && globalTable.at_path(name).is_string())
		{
			return globalTable.at_path(name).as_string()->get();
		}

		dt_error("Value at {} is either not found or does not match type (string)", name);
		return "";
	}

	auto ConfigManager::GetGlobalBoolean(const std::string& name) -> bool
	{
		if (HasGlobalValue(name) && globalTable.at_path(name).is_boolean())
		{
			return globalTable.at_path(name).as_boolean()->get();
		}

		dt_error("Value at {} is either not found or does not match type (bool)", name);
		return false;
	}

	auto ConfigManager::GetGlobalTable(const std::string& name) -> toml::table
	{
		if (HasGlobalValue(name) && globalTable.at_path(name).is_table())
		{
			return *(globalTable.at_path(name).as_table());
		}

		dt_error("Value at {} is either not found or does not match type (table)", name);
		return {};
	}

	auto ConfigManager::GetGlobalArray(const std::string& name) -> toml::array
	{
		if (HasGlobalValue(name) && globalTable.at_path(name).is_array())
		{
			return *(globalTable.at_path(name).as_array());
		}

		dt_error("Value at {} is either not found or does not match type (array)", name);
		return {};
	}

	auto ConfigManager::HasValue(const std::string& name) -> bool
	{
		auto path = toml::path(name);
		const toml::node* currentNode = &appTable;

		for (const auto& key : path)
		{
			if (!currentNode->is_table())
			{
				return false;
			}

			const toml::table& table = *currentNode->as_table();
			currentNode = table.get(key.key());
			if (currentNode == nullptr)
			{
				return false;
			}
		}

		return true;
	}

	auto ConfigManager::HasGlobalValue(const std::string& name) -> bool
	{
		auto path = toml::path(name);
		const toml::node* currentNode = &globalTable;

		for (const auto& key : path)
		{
			if (!currentNode->is_table())
			{
				return false;
			}

			const toml::table& table = *currentNode->as_table();
			currentNode = table.get(key.key());
			if (currentNode == nullptr)
			{
				return false;
			}
		}

		return true;
	}
}