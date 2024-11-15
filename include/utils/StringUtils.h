#pragma once
#include <string>
#include <vector>

/**
 * @brief Replaces every occurrence of a string in a string (confusing, right?)
 * why isn't this on the stdlib again?
 *
 * @param str Original string to modify
 * @param src String to replace
 * @param dest String to replace it *with*
 */
void stringReplace(std::string str, const std::string& src, const std::string& dest);

/**
 * @brief Replaces every character in a string with it's uppercase counterpart
 *
 * @param str String to modify
 * @return std::string Upppercase version of the string
 */
auto stringToUpper(std::string str) -> std::string;

/**
 * @brief Replaces every character in a string with it's lowercase counterpart
 *
 * @param str String to modify
 * @return std::string Lowercase version of the string
 */
auto stringToLower(std::string str) -> std::string;

/**
 * @brief Splits a string via another string
 *
 * @param str String to split
 * @param delimiter String to split from (delimiter)
 * @return std::vector<std::string> Array of the splitted string results
 */
auto stringSplit(const std::string& str, const std::string& delimiter)
	-> std::vector<std::string>;