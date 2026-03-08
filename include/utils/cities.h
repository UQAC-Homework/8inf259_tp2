#ifndef INC_8INF259_TP2_CITIES_H
#define INC_8INF259_TP2_CITIES_H
#include <queue>

#include "../Ville.h"

namespace utils::cities
{
	/// Adds a block to the given city of the given color
	inline void addBlock(Ville& target, const std::string& color)
	{
		// Total count cannot go beyond 3
		if (target.totalCubes() >= 3)
			return;

		if (!target.cubes.contains(color))
			target.cubes.insert({color, 0});

		target.cubes[color]++;
	}

	/// Gets the display name of the color
	inline std::string getColorName(const std::string& color)
	{
		if (color == "blue")
			return "Choléra";

		if (color == "red")
			return "Typhus";

		if (color == "yellow")
			return "Fièvre jaune";

		if (color == "black")
			return "Malaria";

		throw std::logic_error("The color '" + color + "' is not supported.");
	}

	/// Starts to solve the eclosions from the given city
	inline std::size_t solveEclosion(CityGraph& graph, const Ville& city, std::size_t current_eclosion_count)
	{
		std::set<std::string> infected_cities;
		std::queue<std::string> cities_to_process;
		cities_to_process.push(city.nom);
		infected_cities.insert(city.nom);

		while (!cities_to_process.empty())
		{
			const auto& current_name = cities_to_process.front();
			cities_to_process.pop();

			const auto& current_city = graph.getCity(current_name);

			current_eclosion_count++;
			std::cout << "** ECLOSION #" << current_eclosion_count << " a " << current_city.nom << " (" <<
				getColorName(current_city.couleur) << ")" << std::endl;

			for (const auto& neighbor : graph.getNeighbors(current_city.nom, ROAD))
			{
				std::cout << "|-- " << neighbor << " : ";

				if (infected_cities.contains(neighbor))
				{
					std::cout << "ignore (deja en eclosion)" << std::endl;
					continue;
				}

				auto& neighbor_city = graph.getCity(neighbor);

				if (neighbor_city.totalCubes() >= 3)
				{
					std::cout << neighbor_city.totalCubes() << " cubes total -> eclosion en chaine !" << std::endl;
					infected_cities.insert(neighbor);
					cities_to_process.push(neighbor);
					continue;
				}

				std::cout << neighbor_city.totalCubes() << " -> ";
				addBlock(neighbor_city, current_city.couleur);
				std::cout << neighbor_city.totalCubes() << std::endl;
			}
		}

		return current_eclosion_count;
	}
}

#endif //INC_8INF259_TP2_CITIES_H
