#include "core/ApplicationInfo.h"
#include "core/Logger.h"
#include "utils/StringUtils.h"

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
		_env.WorkingDirectory = std::filesystem::current_path();

		char buffer[1024];
		std::string path;

#if defined(_WIN32) || defined(_WIN64)
		DWORD size = GetModuleFileNameA(NULL, buffer, sizeof(buffer));
		if (size > 0 && size < sizeof(buffer))
		{
			path = std::string(buffer, size);
		}
		else
		{
			es_coreError("Unable to get executable path on Windows.");
		}
#elif defined(__APPLE__)
		uint32_t size = sizeof(buffer);
		if (_NSGetExecutablePath(buffer, &size) == 0)
		{
			path = std::string(buffer);
		}
		else
		{
			std::vector<char> largerBuffer(size);
			if (_NSGetExecutablePath(largerBuffer.data(), &size) == 0)
			{
				path = std::string(largerBuffer.data(), size);
			}
			else
			{
				es_coreError("Unable to get executable path on macOS.");
			}
		}
#elif defined(__linux__)
		ssize_t size = readlink("/proc/self/exe", buffer, sizeof(buffer) - 1);
		if (size != -1)
		{
			buffer[size] = '\0';
			path = std::string(buffer);
		}
		else
		{
			es_coreError("Unable to get executable path on Linux.");
		}
#else
		path = std::filesystem::path(_env.WorkingDirectory) / _id.Name;
		es_coreWarn("Unsupported platform at _setupEnvInfo()");
#endif

		_env.ExecutablePath = path;

#if defined(_WIN32) || defined(_WIN64)
		LPWSTR* szArglist;
		int nArgs;
		szArglist = CommandLineToArgvW(GetCommandLineW(), &nArgs);
		if (szArglist)
		{
			for (int i = 0; i < nArgs; ++i)
			{
				std::wstring ws(szArglist[i]);
				_env.CommandLineArgs.push_back(std::string(ws.begin(), ws.end()));
			}
			LocalFree(szArglist);
		}
		else
		{
			es_coreError("Unable to get command line arguments on Windows.");
		}
#elif defined(__APPLE__)
		int argc = *_NSGetArgc();
		char** argv = *_NSGetArgv();
		for (int i = 0; i < argc; ++i)
		{
			_env.CommandLineArgs.push_back(std::string(argv[i]));
		}
#elif defined(__linux__)
		std::ifstream cmdline("/proc/self/cmdline");
		if (cmdline)
		{
			std::string arg;
			while (std::getline(cmdline, arg, '\0'))
			{
				_env.CommandLineArgs.push_back(arg);
			}
		}
		else
		{
			es_coreError("Unable to get command line arguments on Linux.");
		}
#else
		es_coreError("Unsupported platform at _setupEnvInfo().");
#endif

#ifdef DEBUG
		_env.AssetsDirectory =
			std::filesystem::path(_env.ExecutablePath).remove_filename() / "assets";
#else
		_env.AssetsDirectory =
			std::filesystem::path(_env.ExecutablePath).remove_filename() / "assets.pak";
#endif

		_env.RootPath = std::filesystem::path(_env.ExecutablePath).remove_filename();
	}
}