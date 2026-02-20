#ifndef INC_8INF259_TP2_GRAPHPARSER_H
#define INC_8INF259_TP2_GRAPHPARSER_H

#include "../include/string_utils.h"

#include <cassert>
#include <filesystem>
#include <fstream>

#include "Graph.h"
#include "Ville.h"

#define COMMENT_CHAR '#'
#define DIVIDER_CHAR ';'
#define CITY_START "VILLES"
#define LINKS_START "LIENS"

inline Ville createCity(const std::string& line)
{
	const std::vector<std::string> tokens = split(line, DIVIDER_CHAR);

	if (tokens.size() < 3)
		throw std::out_of_range("Line has missing tokens: " + line);

	const std::string& name = tokens.at(0);
	const std::string& color = tokens.at(1);
	const std::string& isPort = tokens.at(2);

	Ville city(name, color, isPort == "1");

	return city;
}

inline std::tuple<std::string, std::string> createLink(const std::string& line)
{
	const std::vector<std::string> tokens = split(line, DIVIDER_CHAR);

	if (tokens.size() < 2)
		throw std::out_of_range("Line has missing tokens: " + line);

	const std::string& origin = tokens.at(0);
	const std::string& destination = tokens.at(1);

	return {origin, destination};
}

inline Graph loadFromStream(std::ifstream& stream)
{
	Graph graph;

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
			Ville newCity = createCity(line);
			graph.addNode(newCity.nom);
		}
		else
		{
			const auto newLink = createLink(line);

			const std::string origin = std::get<0>(newLink);
			const std::string destination = std::get<1>(newLink);

			graph.addLink(origin, destination);
			graph.addLink(destination, origin);
		}
	}

	return graph;
}

#endif //INC_8INF259_TP2_GRAPHPARSER_H