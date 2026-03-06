#ifndef INC_8INF259_TP2_PATHFINDING_H
#define INC_8INF259_TP2_PATHFINDING_H
#include <queue>
#include <string>
#include <vector>

#include "../CityGraph.h"

namespace utils::pathfinding
{
	inline std::vector<std::string> BFS(
		const CityGraph& graph,
		const std::string& start_city,
		const std::string& end_city,
		const TransportMode allowed_transports
	)
	{
		std::queue<std::string> cities_to_visit;
		std::set<std::string> cities_visited;
		std::unordered_map<std::string, std::string> cities_visited_from;
		bool has_found_end = false;

		cities_to_visit.push(start_city);
		cities_visited.insert(start_city);

		while (!has_found_end && !cities_to_visit.empty())
		{
			const std::string current_city = cities_to_visit.front();
			cities_to_visit.pop();

			for (const auto& neighbor_city : graph.getNeighbors(current_city, allowed_transports))
			{
				if (cities_visited.contains(neighbor_city))
					continue;

				cities_visited_from[neighbor_city] = current_city;
				cities_visited.insert(neighbor_city);
				cities_to_visit.push(neighbor_city);

				if (neighbor_city != end_city)
					continue;

				has_found_end = true;
				break;
			}
		}

		std::vector<std::string> path;
		std::string current_city = end_city;

		while (cities_visited_from.contains(current_city))
		{
			path.push_back(current_city);
			current_city = cities_visited_from.at(current_city);
		}

		path.push_back(start_city);

		std::reverse(path.begin(), path.end());

		return path;
	}
}

#endif //INC_8INF259_TP2_PATHFINDING_H
