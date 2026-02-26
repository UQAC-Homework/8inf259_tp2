#include "../../include/Graphs/CityGraph.h"
#include "../../include/Ville.h"

#include <cassert>
#include <fstream>
#include <ranges>

ds::Set<int> CityGraph::getReachableByRoad(const int id) const
{
	return this->_graph.getEdges(id);
}

ds::Set<int> CityGraph::getReachableByTrain(const int id) const
{
	const auto railwayId = this->railCities.at(id);
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
	const auto id = this->_graph.addNode(city);
	this->nameToId[city.nom] = id;

	if (city.port)
		this->boatCities.insert(id);
}

void CityGraph::addRoad(const std::string& from, const std::string& to)
{
	const auto fromID = this->nameToId.at(from);
	const auto toID = this->nameToId.at(to);

	if (this->_graph.areConnected(fromID, toID))
		return;

	this->_graph.addEdge(fromID, toID);
	this->_graph.addEdge(toID, fromID);
}

void CityGraph::addRail(const std::string& from, const std::string& to)
{
	const auto fromID = this->nameToId.at(from);
	const auto toID = this->nameToId.at(to);

	const auto fromHasRailway = this->railCities.contains(fromID);
	const auto toHasRailway = this->railCities.contains(toID);

	if (fromHasRailway && toHasRailway)
	{
		const auto railwayID = this->railCities.at(fromID);
		const auto oldRailwayID = this->railCities.at(toID);

		this->railways[railwayID].insert(toID);
		this->railCities[toID] = railwayID;

		auto oldRailway = this->railways[oldRailwayID];

		oldRailway.erase(toID);

		if (oldRailway.size() == 0)
			this->railways.erase(oldRailwayID);

		return;
	}

	if (fromHasRailway)
	{
		const auto railwayID = this->railCities.at(fromID);
		this->railways[railwayID].insert(toID);
		this->railCities[toID] = railwayID;
		return;
	}

	if (toHasRailway)
	{
		const auto railwayID = this->railCities.at(toID);
		this->railways[railwayID].insert(fromID);
		this->railCities[fromID] = railwayID;
		return;
	}

	// No railway
	const auto railwayID = this->_nextRailwayID;
	this->_nextRailwayID++;

	this->railCities[fromID] = railwayID;
	this->railCities[toID] = railwayID;

	ds::Set<int> newRailway;
	newRailway.insert(fromID);
	newRailway.insert(toID);

	this->railways[railwayID] = newRailway;
}

std::size_t CityGraph::getCityCount() const
{
	return this->_graph.size();
}

std::size_t CityGraph::getRailsCount() const
{
	const auto size = this->railCities.size();

	if (size == 0)
		return 0;

	return size - 1;
}

ds::Set<std::string> CityGraph::getCityNames() const
{
	ds::Set<std::string> names;

	for (const auto& name : this->nameToId | std::views::keys)
		names.insert(name);

	return names;
}

ds::Set<std::string> CityGraph::getNeighbors(const std::string& city, const TransportMode allowedModes) const
{
	if (allowedModes == NONE)
	{
		static const ds::Set<std::string> empty;
		return empty;
	}

	const int cityId = this->nameToId.at(city);
	ds::Set<int> neighborsId;

	if (allowedModes & ROAD)
	{
		for (auto neighbor : this->getReachableByRoad(cityId))
			neighborsId.insert(neighbor);
	}

	if (allowedModes & TRAIN && this->railCities.contains(cityId))
	{
		for (auto neighbor : this->getReachableByTrain(cityId))
			neighborsId.insert(neighbor);
	}

	if (allowedModes & BOAT && this->boatCities.contains(cityId))
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

TransportMode CityGraph::getAvailableTransportModes(const std::string& from, const std::string& to) const
{
	const auto fromID = this->nameToId.at(from);
	const auto toID = this->nameToId.at(to);

	const auto& fromCity = this->_graph.getNode(fromID);
	const auto& toCity = this->_graph.getNode(toID);

	TransportMode transportModes = NONE;

	if (this->_graph.areConnected(fromID, toID))
		transportModes = transportModes | ROAD;

	if (this->railCities.contains(fromID) && this->getReachableByTrain(fromID).contains(toID))
		transportModes = transportModes | TRAIN;

	if (fromCity.port && toCity.port)
		transportModes = transportModes | BOAT;

	return transportModes;
}
