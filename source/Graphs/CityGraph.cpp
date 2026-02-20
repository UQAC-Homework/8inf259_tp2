#include "../../include/Graphs/CityGraph.h"

#include <cassert>
#include <fstream>
#include <stdexcept>

#include "../../include/string_utils.h"
#include "../../include/Ville.h"

std::size_t CityGraph::getCityCount() const
{
	return this->cities.size();
}

CityGraph CityGraph::loadFromStream(std::ifstream& stream)
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
	Map<std::string, int> cityNameToId;

	bool processingCities = false;
	bool processingLinks = false;

	std::string line;
	while (std::getline(stream, line))
	{
		line = trim(line);

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
			const std::vector<std::string> tokens = split(line, DIVIDER_CHAR);

			if (tokens.size() < 3)
				throw std::out_of_range("Line has missing tokens: " + line);

			const std::string& name = tokens.at(0);
			const std::string& color = tokens.at(1);
			const std::string& isPort = tokens.at(2);

			const Ville city(name, color, isPort == "1");
			const int id = graph.addNode();
			graph.cities.set(id, city);
			cityNameToId.set(city.nom, id);
		}
		else
		{
			const std::vector<std::string> tokens = split(line, DIVIDER_CHAR);

			if (tokens.size() < 2)
				throw std::out_of_range("Line has missing tokens: " + line);

			const int origin = cityNameToId.at(tokens.at(0));
			const int destination = cityNameToId.at(tokens.at(1));

			graph.addEdge(origin, destination);
			graph.addEdge(destination, origin);
		}
	}

	return graph;
}
