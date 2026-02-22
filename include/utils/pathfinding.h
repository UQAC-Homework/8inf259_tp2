#ifndef INC_8INF259_TP2_PATHFINDING_H
#define INC_8INF259_TP2_PATHFINDING_H
#include <map>
#include <queue>
#include <set>
#include <stdexcept>
#include <string>
#include <vector>

#include "../Graphs/CityGraph.h"

namespace utils::pathfinding
{
	inline std::vector<std::string> BFS(const CityGraph& graph, const std::string& start, const std::string& end)
	{
		std::set<std::string> visited;
		std::queue<std::string> toVisit;
		std::map<std::string, std::string> visitFrom;

		toVisit.push(start);
		visited.insert(start);

		while (!toVisit.empty())
		{
			const std::string current = toVisit.front();
			toVisit.pop();

			for (const auto& neighbor : graph.getNeighbors(current))
			{
				if (visited.contains(neighbor))
					continue;

				visitFrom[neighbor] = current;
				visited.insert(neighbor);
				toVisit.push(neighbor);
			}
		}

		if (!visitFrom.contains(end))
			throw std::logic_error("No path from '" + start + "' to '" + end + "'.");

		std::vector<std::string> path;
		std::string current = end;

		while (visited.contains(current))
		{
			path.push_back(current);
			current = visitFrom[current];
		}

		std::reverse(path.begin(), path.end());

		return path;
	}
}

#endif //INC_8INF259_TP2_PATHFINDING_H
