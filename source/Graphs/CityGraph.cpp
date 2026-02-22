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
		const int railwayID = this->railCities.at(fromID);
		const int oldRailwayID = this->railCities.at(toID);

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

std::size_t CityGraph::getRailsCount() const
{
	const std::size_t size = this->railCities.size();

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

TransportType CityGraph::getAvailableTransportTypes(const std::string& from, const std::string& to) const
{
	const int fromID = this->nameToId.at(from);
	const int toID = this->nameToId.at(to);

	const Ville& fromCity = this->_graph.getNode(fromID);
	const Ville& toCity = this->_graph.getNode(toID);

	TransportType transportTypes = NONE;

	if (this->_graph.areConnected(fromID, toID))
		transportTypes = static_cast<TransportType>(transportTypes | ROAD);

	if (this->railCities.contains(fromID) && this->getReachableByTrain(fromID).contains(toID))
		transportTypes = static_cast<TransportType>(transportTypes | TRAIN);

	if (fromCity.port && toCity.port)
		transportTypes = static_cast<TransportType>(transportTypes | BOAT);

	return transportTypes;
}
