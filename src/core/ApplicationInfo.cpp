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
}