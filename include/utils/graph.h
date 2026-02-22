#ifndef INC_8INF259_TP2_GRAPH_UTILS_H
#define INC_8INF259_TP2_GRAPH_UTILS_H
#include <cassert>
#include <iosfwd>
#include <vector>

#include "string.h"
#include "../Graphs/CityGraph.h"

namespace utils::graph
{
	/// Loads the graph from the given stream
	inline CityGraph loadGraphFromStream(std::istream& stream)
	{
		// ReSharper disable CppTooWideScopeInitStatement
		// ReSharper disable CppTooWideScope
		constexpr char COMMENT_CHAR = '#';
		constexpr char DIVIDER_CHAR = ';';
		constexpr char CITY_START[] = "VILLES";
		constexpr char LINKS_START[] = "LIENS";
		// ReSharper restore CppTooWideScopeInitStatement
		// ReSharper restore CppTooWideScope

		CityGraph graph;

		bool processingCities = false;
		bool processingLinks = false;

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
				processingCities = true;
				processingLinks = false;
				continue;
			}

			if (line == LINKS_START)
			{
				processingCities = false;
				processingLinks = true;
				continue;
			}

			if (!processingCities && !processingLinks)
				throw std::logic_error("Unhandled line: " + line);

			assert((!processingCities && processingLinks) || (processingCities && !processingLinks));

			if (processingCities)
			{
				const std::vector<std::string> tokens = string::split(line, DIVIDER_CHAR);

				if (tokens.size() < 3)
					throw std::out_of_range("Line has missing tokens: " + line);

				const std::string& name = tokens.at(0);
				const std::string& color = tokens.at(1);
				const std::string& isPort = tokens.at(2);

				const Ville city(name, color, isPort == "1");
				graph.addCity(city);
			}
			else
			{
				const std::vector<std::string> tokens = string::split(line, DIVIDER_CHAR);

				if (tokens.size() < 2)
					throw std::out_of_range("Line has missing tokens: " + line);

				const std::string& origin = tokens.at(0);
				const std::string& destination = tokens.at(1);

				graph.addRoad(origin, destination);
			}
		}

		return graph;
	}
}

#endif //INC_8INF259_TP2_GRAPH_UTILS_H
