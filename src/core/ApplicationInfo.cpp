#include "core/ApplicationInfo.h"
#include "core/Application.h"
#include "core/Logger.h"
#include "utils/StringUtils.h"
#include <filesystem>
#include <fstream>
#include <unistd.h>
#include <pwd.h>

#ifdef DEBUG
#	include <regex>
#endif

namespace Drift
{
	ApplicationID::ApplicationID(const std::string& appId)
	{
		if (!CheckAppID(appId))
		{
			dt_coreFatal("Application ID is invalid");
		}

		auto segments = stringSplit(appId, ".");

		if (segments.size() == 3)
		{
			Domain = segments[0];
			Org = segments[1];
			Name = segments[2];
		}
		else if (segments.size() == 2)
		{
			Org = segments[0];
			Name = segments[1];
		}
		else
		{
			dt_coreFatal("Application ID is invalid! Expected 2-3 segments, got {}",
						 segments.size());
		}
	}

	auto ApplicationID::CheckAppID(const std::string& appId) -> bool
	{
#ifdef DEBUG
		if (!std::regex_match(
				appId, std::regex("[a-zA-Z0-9_-]+\\.[a-zA-Z0-9_-]+(\\.[a-zA-Z0-9_-]+)?")))
		{
			dt_coreError("Application ID \"{}\" is invalid", appId);
			return false;
		}
#endif

		return true;
	}

	auto ApplicationID::GetCompoundID() const -> std::string
	{
		return Domain + "." + Org + "." + Name;
	}

	EnvironmentInfo::EnvironmentInfo()
	{
		WorkingDirectory = std::filesystem::current_path();

		char buffer[1024];
		std::string path;

		ssize_t size = readlink("/proc/self/exe", buffer, sizeof(buffer) - 1);
		if (size != -1)
		{
			buffer[size] = '\0';
			path = std::string(buffer);
		}
		else
		{
			dt_coreError("Unable to get executable path on Linux.");
		}

		ExecutablePath = path;

		std::ifstream cmdline("/proc/self/cmdline");
		if (cmdline)
		{
			std::string arg;
			while (std::getline(cmdline, arg, '\0'))
			{
				CommandLineArgs.push_back(arg);
			}
		}
		else
		{
			dt_coreError("Unable to get command line arguments on Linux.");
		}

		const char* home = std::getenv("HOME");
		if (home != nullptr)
		{
			HomeDirectory = std::string(home);
		}
		else
		{
			struct passwd* pwd = getpwuid(getuid());
			if (pwd != nullptr)
			{
				HomeDirectory = std::string(pwd->pw_dir);
			}
		}

#ifdef DEBUG
		AssetsDirectory =
			std::filesystem::path(ExecutablePath).remove_filename() / "assets";
#else
		AssetsDirectory = ":";
#endif

		RootPath = std::filesystem::path(ExecutablePath).remove_filename();

		if (HasFlag("--verbose") || HasFlag("-v"))
		{
			Verbose = true;
		}

		ApplicationDirectory = std::filesystem::path(HomeDirectory) / ".config" / "drift" / "apps" / stringToLower(Application::GetApplicationID().GetCompoundID());
	}

	auto EnvironmentInfo::HasFlag(const std::string& flag) -> bool
	{
		return std::find(CommandLineArgs.begin(), CommandLineArgs.end(), flag) !=
			   CommandLineArgs.end();
	}
}