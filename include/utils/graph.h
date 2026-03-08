#ifndef INC_8INF259_TP2_GRAPH_UTILS_H
#define INC_8INF259_TP2_GRAPH_UTILS_H
#include <cassert>
#include <iosfwd>

#include "../CityGraph.h"
#include "../utils/string.h"

namespace utils::graph
{
	/// Loads the graph from the given stream
	inline CityGraph loadGraphFromStream(std::istream& stream)
	{
#define COMMENT_CHAR '#'
#define DIVIDER_CHAR ';'
#define CITY_START "VILLES"
#define LINKS_START "LIENS"

		CityGraph graph;

		bool processing_cities = false;
		bool processing_links = false;

		std::string line;
		while (std::getline(stream, line))
		{
			line = string::trim(line);

			if (line.empty())
				continue;

			if (line.at(0) == COMMENT_CHAR)
				continue;

			if (line == CITY_START)
			{
				processing_cities = true;
				processing_links = false;
				continue;
			}

			if (line == LINKS_START)
			{
				processing_cities = false;
				processing_links = true;
				continue;
			}

			if (!processing_cities && !processing_links)
				throw std::logic_error("Unhandled line: " + line);

			assert((!processing_cities && processing_links) || (processing_cities && !processing_links));

			if (processing_cities)
			{
				const auto tokens = string::split(line, DIVIDER_CHAR);

				if (tokens.size() < 3)
					throw std::out_of_range("Line has missing tokens: " + line);

				const auto& name = tokens.at(0);
				const auto& color = tokens.at(1);
				const auto& is_port = tokens.at(2);

				const Ville city(name, color, is_port == "1");
				graph.addCity(city);
			}
			else
			{
				const auto tokens = string::split(line, DIVIDER_CHAR);

				if (tokens.size() < 2)
					throw std::out_of_range("Line has missing tokens: " + line);

				const auto& origin = tokens.at(0);
				const auto& destination = tokens.at(1);

				graph.addRoad(origin, destination);
			}
		}

		return graph;
	}
}

#endif //INC_8INF259_TP2_GRAPH_UTILS_H
