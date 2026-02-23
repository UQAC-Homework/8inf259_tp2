#ifndef INC_8INF259_TP2_PATHFINDING_H
#define INC_8INF259_TP2_PATHFINDING_H
#include <queue>
#include <string>
#include <vector>

#include "../Graphs/CityGraph.h"

namespace utils::pathfinding
{
	inline std::vector<std::string> BFS(
		const CityGraph& graph,
		const std::string& startCity,
		const std::string& endCity,
		const TransportMode allowedTransports
	)
	{
		std::queue<std::string> citiesToVisit;
		ds::Set<std::string> citiesVisited;
		ds::Map<std::string, std::string> citiesVisitedFrom;
		bool hasFoundEnd = false;

		citiesToVisit.push(startCity);
		citiesVisited.insert(startCity);

		while (!hasFoundEnd && !citiesToVisit.empty())
		{
			const std::string currentCity = citiesToVisit.front();
			citiesToVisit.pop();

			for (const auto& neighborCity : graph.getNeighbors(currentCity, allowedTransports))
			{
				if (citiesVisited.contains(neighborCity))
					continue;

				citiesVisitedFrom.insert(neighborCity, currentCity);
				citiesVisited.insert(neighborCity);
				citiesToVisit.push(neighborCity);

				if (neighborCity != endCity)
					continue;

				hasFoundEnd = true;
				break;
			}
		}

		std::vector<std::string> path;
		std::string currentCity = endCity;

		while (citiesVisitedFrom.contains(currentCity))
		{
			path.push_back(currentCity);
			currentCity = citiesVisitedFrom.at(currentCity);
		}

		path.push_back(startCity);

		std::reverse(path.begin(), path.end());

		return path;
	}
}

#endif //INC_8INF259_TP2_PATHFINDING_H
