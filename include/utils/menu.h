#ifndef INC_8INF259_TP2_MENU_UTILS_H
#define INC_8INF259_TP2_MENU_UTILS_H
#include <climits>
#include <tuple>
#include <utility>
#include <vector>

namespace utils::menu
{
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

		// ReSharper disable once CppTooWideScopeInitStatement
		int choice = -1;

		if (input >> choice)
			return choice;

		input.clear();
		input.ignore(INT_MAX, '\n');

		return -1;
	}

	inline std::string chooseCity(
		std::ostream& output,
		std::istream& input,
		const std::set<std::string>& cities
	)
	{
		std::vector<std::string> city_names;
		std::vector<std::tuple<int, std::string>> options;

		int index = 1;

		for (const auto& name : cities)
		{
			city_names.push_back(name);
			options.emplace_back(index, name);
			index++;
		}

		while (true)
		{
			const int choice = askChoice(output, input, options);

			if (choice <= 0 || choice > city_names.size())
			{
				output << "Choix invalide." << std::endl;
				continue;
			}

			return city_names[choice - 1];
		}
	}

	inline void displayPath(
		std::ostream& output,
		const std::vector<std::string>& path,
		const CityGraph& graph
	)
	{
		for (int i = 0; i < path.size(); ++i)
		{
			output << path[i];

			if (i > 0)
			{
				const auto mode = graph.getAvailableTransportModes(
					path[i - 1],
					path[i]
				);
				
				if (mode & ROAD)
				{
					//output << " [ROUTE]";
				}
				else if (mode & TRAIN)
					output << " [TRAIN]";
				else if (mode & BOAT)
					output << " [MER]";
			}

			if (i != path.size() - 1)
				output << " -> ";
		}
		output << std::endl;
	}
}

#endif //INC_8INF259_TP2_MENU_UTILS_H
