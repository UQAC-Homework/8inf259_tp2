#ifndef INC_8INF259_TP2_CITIES_H
#define INC_8INF259_TP2_CITIES_H
#include <queue>

#include "../Ville.h"

namespace utils::cities
{
	/// Adds a block from the given city to the given city
	inline void addBlock(const Ville& source, Ville& target)
	{
		// Total count cannot go beyond 3
		if (target.totalCubes() >= 3)
			return;

		const std::string color = source.couleur;
		
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
		
		return color;
	}
	
	/// Starts to solve the eclosions from the given city
	inline std::size_t solveEclosion(CityGraph& graph, const Ville& city, std::size_t currentEclosionCount)
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
			
			currentEclosionCount++;
			std::cout << "** ECLOSION #" << currentEclosionCount << " a " << current_city.nom << " (" << getColorName(current_city.couleur) << ")" << std::endl;

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
				addBlock(current_city, neighbor_city);
				std::cout << neighbor_city.totalCubes() << std::endl;
			}
		}
		
		return currentEclosionCount;
	}
}

#endif //INC_8INF259_TP2_CITIES_H