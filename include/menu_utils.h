#ifndef INC_8INF259_TP2_MENU_UTILS_H
#define INC_8INF259_TP2_MENU_UTILS_H
#include <climits>
#include <iostream>
#include <tuple>
#include <utility>
#include <vector>

inline int askChoice(
	std::ostream& output,
	std::istream& input,
	const std::vector<std::tuple<int, std::string>>& options
)
{
	output << std::endl;
	output << "+======================================+" << std::endl;
	output << "|       PANDEMIC IBERIA -- MENU        |" << std::endl;
	output << "+======================================+" << std::endl;

	for (auto option : options)
	{
		const int index = std::get<0>(option);
		const std::string value = std::get<1>(option);

		output << "\t" << index << ". " << value << std::endl;
	}

	output << "+======================================+" << std::endl;
	output << "> Choix : ";

	int choice = -1;

	if (input >> choice)
		return choice;

	input.clear();
	input.ignore(INT_MAX, '\n');

	return -1;
}

#endif //INC_8INF259_TP2_MENU_UTILS_H
