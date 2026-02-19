#ifndef INC_8INF259_TP2_STRING_UTILS_H
#define INC_8INF259_TP2_STRING_UTILS_H

#include <string>

// From: https://gist.github.com/dedeexe/9080526 (Modified)
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

// From: https://gist.github.com/dedeexe/9080526 (Modified)
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

// From: https://gist.github.com/dedeexe/9080526 (Modified)
//
//Left and Right trim
//
inline std::string trim(const std::string& str)
{
	return trim_left(trim_right(str));
}

// From: https://stackoverflow.com/a/46931770 (Modified)
inline std::vector<std::string> split(const std::string& s, const char delimiter)
{
	size_t pos_start = 0;
	size_t pos_end = 0;
	std::vector<std::string> res;

	while ((pos_end = s.find(delimiter, pos_start)) != std::string::npos)
	{
		std::string token = s.substr(pos_start, pos_end - pos_start);
		pos_start = pos_end + 1;
		res.push_back(token);
	}

	res.push_back(s.substr(pos_start));
	return res;
}

#endif //INC_8INF259_TP2_STRING_UTILS_H
