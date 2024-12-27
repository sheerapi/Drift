#pragma once
#include "toml++/toml.hpp" // IWYU pragma: keep
#include "core/Macros.h"

namespace Drift
{
    class dt_api ConfigManager
    {
    public:
        static void Init();

        static auto GetInteger(const std::string& name) -> long;
        static auto GetDouble(const std::string& name) -> double;
        static auto GetString(const std::string& name) -> std::string;
        static auto GetBoolean(const std::string& name) -> bool;
        static auto GetTable(const std::string& name) -> toml::table;
        static auto GetArray(const std::string& name) -> toml::array;
		static auto GetRootTable() -> toml::table;

		static void SetInteger(const std::string& name, long val);
		static void SetDouble(const std::string& name, double val);
		static void SetString(const std::string& name, const std::string& val);
		static void SetBoolean(const std::string& name, bool val);
		static void SetTable(const std::string& name, toml::table val);
		static void SetArray(const std::string& name, toml::array val);

		static auto HasValue(const std::string& name) -> bool;

		static auto GetGlobalInteger(const std::string& name) -> long;
		static auto GetGlobalDouble(const std::string& name) -> double;
		static auto GetGlobalString(const std::string& name) -> std::string;
		static auto GetGlobalBoolean(const std::string& name) -> bool;
		static auto GetGlobalTable(const std::string& name) -> toml::table;
		static auto GetGlobalArray(const std::string& name) -> toml::array;
		static auto GetGlobalStringArray(const std::string& name)
			-> std::vector<std::string>;

		static auto HasGlobalValue(const std::string& name) -> bool;

	private:
        inline static toml::table appTable;
        inline static toml::table globalTable;

        static void Write();

        template<typename T>
        static void Insert(const std::string& name, T val)
        {
			size_t pos = 0;
			toml::table* currentTable = &appTable;
			std::string token;
			std::string remainingPath = name;

			while ((pos = remainingPath.find('.')) != std::string::npos)
			{
				token =
					remainingPath.substr(0, pos);
				remainingPath.erase(0, pos + 1);

				toml::node* node = currentTable->get(token);
				if ((node == nullptr) || !node->is_table())
				{
					currentTable->insert_or_assign(token, toml::table{});
				}

				currentTable = &*currentTable->get(token)->as_table();
			}

			currentTable->insert_or_assign(remainingPath, val);
            Write();
		}

        friend class Application;
    };
}