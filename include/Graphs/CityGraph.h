#ifndef INC_8INF259_TP2_CITYGRAPH_H
#define INC_8INF259_TP2_CITYGRAPH_H
#include "../TransportMode.h"
#include "../Ville.h"
#include "../ds/Graph.h"

/// Graph that represents a network of cities
class CityGraph
{
	ds::Graph<Ville> _graph;
	std::unordered_map<std::string, int> nameToId;
	int _nextRailwayID;
	std::unordered_map<int, int> railCities;
	std::unordered_map<int, std::set<int>> railways;
	std::set<int> boatCities;

	/// Gets all cities reachable from the given city by road
	[[nodiscard]] std::set<int> getReachableByRoad(int id) const;

	/// Gets all cities reachable from the given city by train
	[[nodiscard]] std::set<int> getReachableByTrain(int id) const;

	/// Gets all cities reachable from the given city by boat
	[[nodiscard]] std::set<int> getReachableByBoat(int id) const;

public:
	CityGraph();
	~CityGraph();

	/// Adds a city on the graph
	void addCity(const Ville& city);

	/// Adds a road between the cities with the given names
	void addRoad(const std::string& from, const std::string& to);

	/// Adds a rail between the cities with the given names
	void addRail(const std::string& from, const std::string& to);

	/// Gets the amount of cities on the graph
	[[nodiscard]] std::size_t getCityCount() const;
	
	/// Gets the amount of rails on the graph
	[[nodiscard]] std::size_t getRailsCount() const;

	/// Gets all the cities by name
	[[nodiscard]] std::set<std::string> getCityNames() const;

	/// Gets the city with the given name
	[[nodiscard]] const Ville& getCity(const std::string& name) const;
	
	/// Gets the city with the given name
	[[nodiscard]] Ville& getCity(const std::string& name);

	/// Gets all the cities neighboring the given city 
	[[nodiscard]] std::set<std::string> getNeighbors(const std::string& city, TransportMode allowedModes) const;

	/// Gets all the connections available between the given cities
	[[nodiscard]] TransportMode getAvailableTransportModes(const std::string& from, const std::string& to) const;
};


#endif //INC_8INF259_TP2_CITYGRAPH_H
