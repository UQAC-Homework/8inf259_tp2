#ifndef INC_8INF259_TP2_CITYGRAPH_H
#define INC_8INF259_TP2_CITYGRAPH_H
#include "../Ville.h"
#include "../ds/Graph.h"
#include "../ds/Map.h"
#include "../ds/Set.h"

/// Every possible transport type
enum TransportType : char
{
	NONE = 0,
	ROAD = 1,
	TRAIN = 1 << 1,
	BOAT = 1 << 2,
	ALL = ROAD | TRAIN | BOAT
};

/// Graph that represents a network of cities
class CityGraph
{
	ds::Graph<Ville, TransportType> _graph;
	ds::Map<std::string, int> nameToId;
	ds::Set<int> boatCities;

	/// Adds a connection of the given type between the cities with the given names 
	void addConnection(const std::string& from, const std::string& to, TransportType type);

	/// Gets all cities accessible by the given city by road
	[[nodiscard]] ds::Set<int> getCitiesAccessibleByRoad(int id) const;

	/// Gets all cities accessible by the given city by train
	[[nodiscard]] ds::Set<int> getCitiesAccessibleByTrain(int id) const;

	/// Gets all cities accessible by the given city by boat
	[[nodiscard]] ds::Set<int> getCitiesAccessibleByBoat(int id) const;

public:
	/// Adds a city on the graph
	void addCity(const Ville& city);

	/// Adds a road between the cities with the given names
	void addRoad(const std::string& from, const std::string& to);

	/// Adds a rail between the cities with the given names
	void addRail(const std::string& from, const std::string& to);

	/// Gets the amount of cities on the graph
	[[nodiscard]] std::size_t getCityCount() const;

	/// Gets all the cities by name
	[[nodiscard]] ds::Set<std::string> getCityNames() const;

	/// Gets all the cities neighboring the given city 
	[[nodiscard]] ds::Set<std::string> getNeighbors(const std::string& city) const;

	/// Loads the graph from the given stream
	static CityGraph loadFromStream(std::ifstream& stream);
};


#endif //INC_8INF259_TP2_CITYGRAPH_H
