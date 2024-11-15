#include "utils/StringUtils.h"
#include <algorithm>

void stringReplace(std::string str, const std::string& src, const std::string& dest)
{
	if (src.empty())
	{
		return;
	}
	size_t start_pos = 0;
	while ((start_pos = str.find(src, start_pos)) != std::string::npos)
	{
		str.replace(start_pos, src.length(), dest);
		start_pos += dest.length();
	}
}

auto stringToUpper(std::string str) -> std::string
{
	std::transform(str.begin(), str.end(), str.begin(), ::toupper);

	return str;
}

auto stringToLower(std::string str) -> std::string
{
	std::transform(str.begin(), str.end(), str.begin(), ::tolower);

	return str;
}

auto stringSplit(const std::string& str, const std::string& delimiter)
	-> std::vector<std::string>
{
	size_t pos_start = 0;
	size_t pos_end;
	size_t delim_len = delimiter.length();
	std::string token;
	std::vector<std::string> res;

	while ((pos_end = str.find(delimiter, pos_start)) != std::string::npos)
	{
		token = str.substr(pos_start, pos_end - pos_start);
		pos_start = pos_end + delim_len;
		res.push_back(token);
	}

	res.push_back(str.substr(pos_start));
	return res;
}