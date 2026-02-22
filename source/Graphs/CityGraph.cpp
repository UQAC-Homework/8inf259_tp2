#include "../../include/Graphs/CityGraph.h"

#include <cassert>
#include <fstream>
#include <ranges>
#include <stdexcept>

#include "../../include/Ville.h"
#include "../../include/utils/string.h"

ds::Set<int> CityGraph::getReachableByRoad(const int id) const
{
	return this->_graph.getEdges(id);
}

ds::Set<int> CityGraph::getReachableByTrain(const int id) const
{
	const int railwayId = this->railCities.at(id);
	return this->railways.at(railwayId);
}

ds::Set<int> CityGraph::getReachableByBoat(int id) const
{
	return this->boatCities;
}

CityGraph::CityGraph()
{
	this->_nextRailwayID = 0;
}

CityGraph::~CityGraph() = default;

void CityGraph::addCity(const Ville& city)
{
	const int id = this->_graph.addNode(city);
	this->nameToId.insert(city.nom, id);

	if (city.port)
		this->boatCities.insert(id);
}

void CityGraph::addRoad(const std::string& from, const std::string& to)
{
	if (!this->nameToId.contains(from))
		throw std::logic_error("No city named '" + from + "' was added.");

	if (!this->nameToId.contains(to))
		throw std::logic_error("No city named '" + to + "' was added.");

	const int fromID = this->nameToId.at(from);
	const int toID = this->nameToId.at(to);

	if (this->_graph.areConnected(fromID, toID))
		return;

	this->_graph.addEdge(fromID, toID);
	this->_graph.addEdge(toID, fromID);
}

void CityGraph::addRail(const std::string& from, const std::string& to)
{
	const int fromID = this->nameToId.at(from);
	const int toID = this->nameToId.at(to);

	const bool fromHasRailway = this->railCities.contains(fromID);
	const bool toHasRailway = this->railCities.contains(toID);

	if (fromHasRailway && toHasRailway)
	{
		// BOTH has railway
		return;
	}

	if (fromHasRailway)
	{
		const int railwayID = this->railCities.at(fromID);
		this->railways[railwayID].insert(toID);
		this->railCities.insert(toID, railwayID);
		return;
	}

	if (toHasRailway)
	{
		const int railwayID = this->railCities.at(toID);
		this->railways[railwayID].insert(fromID);
		this->railCities.insert(fromID, railwayID);
		return;
	}

	// No railway
	const int railwayID = this->_nextRailwayID;
	this->_nextRailwayID++;

	this->railCities.insert(fromID, railwayID);
	this->railCities.insert(toID, railwayID);

	ds::Set<int> newRailway;
	newRailway.insert(fromID);
	newRailway.insert(toID);

	this->railways.insert(railwayID, newRailway);
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

ds::Set<std::string> CityGraph::getNeighbors(const std::string& city, const TransportType allowedTypes) const
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
		for (auto neighbor : this->getReachableByRoad(cityId))
			neighborsId.insert(neighbor);
	}

	if (allowedTypes & TRAIN && this->railCities.contains(cityId))
	{
		for (auto neighbor : this->getReachableByTrain(cityId))
			neighborsId.insert(neighbor);
	}

	if (allowedTypes & BOAT && this->boatCities.contains(cityId))
	{
		for (auto neighbor : this->getReachableByBoat(cityId))
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
