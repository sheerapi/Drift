#pragma once
#include "toml++/toml.hpp" // IWYU pragma: keep
#include "core/Macros.h"

namespace Drift
{
    class dt_api ConfigManager
    {
    public:
        static void Init();

        static auto GetInt(const std::string& name) -> int;
        static auto GetDouble(const std::string& name) -> double;
        static auto GetString(const std::string& name) -> std::string;
        static auto GetBoolean(const std::string& name) -> bool;
        static auto GetTable(const std::string& name) -> toml::table;
        static auto GetArray(const std::string& name) -> toml::array;
		static auto GetRootTable() -> toml::table;

		static void SetInt(const std::string& name, int val);
		static void SetDouble(const std::string& name, double val);
		static void SetString(const std::string& name, const std::string& val);
		static void SetBoolean(const std::string& name, bool val);
		static void SetTable(const std::string& name, toml::table val);
		static void SetArray(const std::string& name, toml::array val);

		static auto HasValue(const std::string& name) -> bool;

		static auto GetGlobalInt(const std::string& name) -> int;
		static auto GetGlobalDouble(const std::string& name) -> double;
		static auto GetGlobalString(const std::string& name) -> std::string;
		static auto GetGlobalBoolean(const std::string& name) -> bool;
		static auto GetGlobalTable(const std::string& name) -> toml::table;
		static auto GetGlobalArray(const std::string& name) -> toml::array;

		static auto HasGlobalValue(const std::string& name) -> bool;

	private:
        inline static toml::table appTable;
        inline static toml::table globalTable;

        static void Write();

        friend class Application;
    };
}