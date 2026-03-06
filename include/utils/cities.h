#ifndef INC_8INF259_TP2_CITIES_H
#define INC_8INF259_TP2_CITIES_H
#include <queue>

#include "../Ville.h"

namespace utils::cities
{
	/// Adds a block from the given city to the given city
	inline void addBlock(const Ville& source, Ville& target)
	{
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
		std::set<std::string> infectedCities;
		std::queue<std::string> citiesToProcess;
		citiesToProcess.push(city.nom);
		infectedCities.insert(city.nom);
		
		while (!citiesToProcess.empty())
		{
			const auto currentName = citiesToProcess.front();
			citiesToProcess.pop();
			
			auto currentCity = graph.getCity(currentName);
			
			currentEclosionCount++;
			std::cout << "** ECLOSION #" << currentEclosionCount << " a " << currentCity.nom << " (" << getColorName(currentCity.couleur) << ")" << std::endl;

			for (auto neighbor : graph.getNeighbors(currentCity.nom, ROAD))
			{
				std::cout << "|-- " << neighbor << " : ";
				
				if (infectedCities.contains(neighbor))
				{
					std::cout << "ignore (deja en eclosion)" << std::endl;
					continue;
				}
				
				auto& neighborCity = graph.getCity(neighbor);
				
				if (neighborCity.totalCubes() >= 3)
				{
					std::cout << neighborCity.totalCubes() << " cubes total -> eclosion en chaine !" << std::endl;
					infectedCities.insert(neighbor);
					citiesToProcess.push(neighbor);
					continue;
				}
					
				std::cout << neighborCity.totalCubes() << " -> ";
				addBlock(currentCity, neighborCity);
				std::cout << neighborCity.totalCubes() << std::endl;
			}
		}
		
		return currentEclosionCount;
	}
}

#endif //INC_8INF259_TP2_CITIES_H