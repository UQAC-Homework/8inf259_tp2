// From: https://gist.github.com/dedeexe/9080526
// Modified

#ifndef INC_8INF259_TP2_STRING_UTILS_H
#define INC_8INF259_TP2_STRING_UTILS_H

#include <string>

//
//Left trim
//
inline std::string trim_left(const std::string& str)
{
	if (str.empty())
		return str;

	const std::string pattern = " \f\n\r\t\v";
	return str.substr(str.find_first_not_of(pattern));
}

//
//Right trim
//
inline std::string trim_right(const std::string& str)
{
	if (str.empty())
		return str;

	const std::string pattern = " \f\n\r\t\v";
	return str.substr(0, str.find_last_not_of(pattern) + 1);
}

//
//Left and Right trim
//
inline std::string trim(const std::string& str)
{
	return trim_left(trim_right(str));
}

#endif //INC_8INF259_TP2_STRING_UTILS_H