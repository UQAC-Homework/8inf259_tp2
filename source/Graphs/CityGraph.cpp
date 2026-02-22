#include "../../include/Graphs/CityGraph.h"

#include <cassert>
#include <fstream>
#include <ranges>
#include <stdexcept>

#include "../../include/Ville.h"
#include "../../include/utils/string.h"

void CityGraph::addConnection(const std::string& from, const std::string& to, const TransportType type)
{
	if (!this->nameToId.contains(from))
		throw std::logic_error("No city named '" + from + "' was added.");

	if (!this->nameToId.contains(to))
		throw std::logic_error("No city named '" + to + "' was added.");

	const int fromId = this->nameToId.at(from);
	const int toId = this->nameToId.at(to);

	if (this->_graph.areConnected(fromId, toId))
	{
		TransportType edge = this->_graph.removeEdge(fromId, toId);
		edge = static_cast<TransportType>(edge | type);
		this->_graph.addEdge(fromId, toId, edge);
	}
	else
		this->_graph.addEdge(fromId, toId, type);
}

ds::Set<int> CityGraph::getCitiesAccessibleByRoad(const int id) const
{
	ds::Set<int> neighbors;

	for (const auto [cityId, edgeType] : this->_graph.getEdges(id))
	{
		if (!(edgeType & ROAD))
			continue;

		neighbors.insert(cityId);
	}

	return neighbors;
}

ds::Set<int> CityGraph::getCitiesAccessibleByTrain(int id) const
{
	ds::Set<int> neighbors;

	return neighbors;
}

ds::Set<int> CityGraph::getCitiesAccessibleByBoat(int id) const
{
	return this->boatCities;
}

void CityGraph::addCity(const Ville& city)
{
	const int id = this->_graph.addNode(city);
	this->nameToId.insert(city.nom, id);

	if (city.port)
		this->boatCities.insert(id);
}

void CityGraph::addRoad(const std::string& from, const std::string& to)
{
	this->addConnection(from, to, ROAD);
	this->addConnection(to, from, ROAD);
}

void CityGraph::addRail(const std::string& from, const std::string& to)
{
	this->addConnection(from, to, TRAIN);
	this->addConnection(to, from, TRAIN);
}

std::size_t CityGraph::getCityCount() const
{
	return this->_graph.size();
}

ds::Set<std::string> CityGraph::getCityNames() const
{
	ds::Set<std::string> names;

	for (const auto& name : this->nameToId | std::views::keys)
		names.insert(name);

	return names;
}

ds::Set<std::string> CityGraph::getNeighbors(const std::string& city, TransportType allowedTypes) const
{
	if (allowedTypes == NONE)
	{
		static const ds::Set<std::string> empty;
		return empty;
	}

	const int cityId = this->nameToId.at(city);
	ds::Set<int> neighborsId;

	if (allowedTypes & ROAD)
	{
		for (auto neighbor : this->getCitiesAccessibleByRoad(cityId))
			neighborsId.insert(neighbor);
	}

	if (allowedTypes & TRAIN)
	{
		for (auto neighbor : this->getCitiesAccessibleByTrain(cityId))
			neighborsId.insert(neighbor);
	}

	if (allowedTypes & BOAT && this->boatCities.contains(cityId))
	{
		for (auto neighbor : this->getCitiesAccessibleByBoat(cityId))
			neighborsId.insert(neighbor);
	}

	ds::Set<std::string> neighborsName;

	for (const auto neighborId : neighborsId)
	{
		const Ville& neighbor = this->_graph.getNode(neighborId);
		neighborsName.insert(neighbor.nom);
	}

	return neighborsName;
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
		line = utils::string::trim(line);

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
			const std::vector<std::string> tokens = utils::string::split(line, DIVIDER_CHAR);

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
			const std::vector<std::string> tokens = utils::string::split(line, DIVIDER_CHAR);

			if (tokens.size() < 2)
				throw std::out_of_range("Line has missing tokens: " + line);

			const std::string& origin = tokens.at(0);
			const std::string& destination = tokens.at(1);

			graph.addRoad(origin, destination);
		}
	}

	return graph;
}
