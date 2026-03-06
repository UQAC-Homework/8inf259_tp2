#include "../include/CityGraph.h"
#include "../include/Ville.h"

#include <cassert>
#include <fstream>
#include <ranges>

std::set<int> CityGraph::getReachableByRoad(const int id) const
{
	return this->_graph.getEdges(id);
}

std::set<int> CityGraph::getReachableByTrain(const int id) const
{
	const auto railway_id = this->_railCities.at(id);
	return this->_railways.at(railway_id);
}

std::set<int> CityGraph::getReachableByBoat() const
{
	return this->_boatCities;
}

CityGraph::CityGraph()
{
	this->_nextRailwayId = 0;
}

CityGraph::~CityGraph() = default;

void CityGraph::addCity(const Ville& city)
{
	const auto id = this->_graph.addNode(city);
	this->_nameToId[city.nom] = id;

	if (city.port)
		this->_boatCities.insert(id);
}

void CityGraph::addRoad(const std::string& from, const std::string& to)
{
	const auto from_id = this->_nameToId.at(from);
	const auto to_id = this->_nameToId.at(to);

	if (this->_graph.hasEdge(from_id, to_id))
		return;

	this->_graph.addEdge(from_id, to_id);
	this->_graph.addEdge(to_id, from_id);
}

void CityGraph::addRail(const std::string& from, const std::string& to)
{
	const auto from_id = this->_nameToId.at(from);
	const auto to_id = this->_nameToId.at(to);

	const auto from_has_railway = this->_railCities.contains(from_id);
	const auto to_has_railway = this->_railCities.contains(to_id);

	if (from_has_railway && to_has_railway)
	{
		const auto railway_id = this->_railCities.at(from_id);
		const auto old_railway_id = this->_railCities.at(to_id);

		this->_railways[railway_id].insert(to_id);
		this->_railCities[to_id] = railway_id;

		auto old_railway = this->_railways[old_railway_id];

		old_railway.erase(to_id);

		if (old_railway.size() == 0)
			this->_railways.erase(old_railway_id);

		return;
	}

	if (from_has_railway)
	{
		const auto railway_id = this->_railCities.at(from_id);
		this->_railways[railway_id].insert(to_id);
		this->_railCities[to_id] = railway_id;
		return;
	}

	if (to_has_railway)
	{
		const auto railway_id = this->_railCities.at(to_id);
		this->_railways[railway_id].insert(from_id);
		this->_railCities[from_id] = railway_id;
		return;
	}

	// No railway
	const auto railway_id = this->_nextRailwayId;
	this->_nextRailwayId++;

	this->_railCities[from_id] = railway_id;
	this->_railCities[to_id] = railway_id;

	std::set<int> new_railway;
	new_railway.insert(from_id);
	new_railway.insert(to_id);

	this->_railways[railway_id] = new_railway;
}

std::size_t CityGraph::getCityCount() const
{
	return this->_graph.size();
}

std::size_t CityGraph::getRailsCount() const
{
	const auto size = this->_railCities.size();

	if (size == 0)
		return 0;

	return size - 1;
}

std::set<std::string> CityGraph::getCityNames() const
{
	std::set<std::string> names;

	for (const auto& name : this->_nameToId | std::views::keys)
		names.insert(name);

	return names;
}

const Ville& CityGraph::getCity(const std::string& name) const
{
	const int city_id = this->_nameToId.at(name);
	return this->_graph.getNode(city_id);
}

Ville& CityGraph::getCity(const std::string& name)
{
	const int city_id = this->_nameToId.at(name);
	return this->_graph.getNode(city_id);
}

std::set<std::string> CityGraph::getNeighbors(const std::string& city, const TransportMode allowed_modes) const
{
	if (allowed_modes == NONE)
	{
		static const std::set<std::string> EMPTY;
		return EMPTY;
	}

	const int city_id = this->_nameToId.at(city);
	std::set<int> neighbors_id;

	if (allowed_modes & ROAD)
	{
		for (auto neighbor : this->getReachableByRoad(city_id))
			neighbors_id.insert(neighbor);
	}

	if (allowed_modes & TRAIN && this->_railCities.contains(city_id))
	{
		for (auto neighbor : this->getReachableByTrain(city_id))
			neighbors_id.insert(neighbor);
	}

	if (allowed_modes & BOAT && this->_boatCities.contains(city_id))
	{
		for (auto neighbor : this->getReachableByBoat())
			neighbors_id.insert(neighbor);
	}

	std::set<std::string> neighbors_name;

	for (const auto neighbor_id : neighbors_id)
	{
		const Ville& neighbor = this->_graph.getNode(neighbor_id);
		neighbors_name.insert(neighbor.nom);
	}

	return neighbors_name;
}

TransportMode CityGraph::getAvailableTransportModes(const std::string& from, const std::string& to) const
{
	const auto from_id = this->_nameToId.at(from);
	const auto to_id = this->_nameToId.at(to);

	const auto& from_city = this->_graph.getNode(from_id);
	const auto& to_city = this->_graph.getNode(to_id);

	TransportMode transport_modes = NONE;

	if (this->_graph.hasEdge(from_id, to_id))
		transport_modes = transport_modes | ROAD;

	if (this->_railCities.contains(from_id) && this->getReachableByTrain(from_id).contains(to_id))
		transport_modes = transport_modes | TRAIN;

	if (from_city.port && to_city.port)
		transport_modes = transport_modes | BOAT;

	return transport_modes;
}
