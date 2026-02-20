#include "../../include/Graphs/CityGraph.h"

#include <cassert>
#include <fstream>
#include <stdexcept>

#include "../../include/string_utils.h"
#include "../../include/Ville.h"

void CityGraph::addCity(const Ville& city)
{
	const int id = this->addNode(city);
	this->nameToId.insert(city.nom, id);
}

void CityGraph::addRoad(const std::string& from, const std::string& to)
{
	if (!this->nameToId.contains(from))
		throw std::logic_error("No such city name: " + from);

	if (!this->nameToId.contains(to))
		throw std::logic_error("No such city name: " + to);

	const int fromId = this->nameToId.at(from);
	const int toId = this->nameToId.at(to);

	this->addEdge(fromId, toId);
	this->addEdge(toId, fromId);
}

std::size_t CityGraph::getCityCount() const
{
	return this->nameToId.size();
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
			graph.addCity(city);
		}
		else
		{
			const std::vector<std::string> tokens = split(line, DIVIDER_CHAR);

			if (tokens.size() < 2)
				throw std::out_of_range("Line has missing tokens: " + line);

			const std::string& origin = tokens.at(0);
			const std::string& destination = tokens.at(1);

			graph.addRoad(origin, destination);
		}
	}

	return graph;
}
