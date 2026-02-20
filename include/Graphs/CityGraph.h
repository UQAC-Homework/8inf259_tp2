#ifndef INC_8INF259_TP2_CITYGRAPH_H
#define INC_8INF259_TP2_CITYGRAPH_H
#include "BaseGraph.h"
#include "../Map.h"
#include "../Ville.h"

/// Graph that represents a network of cities
class CityGraph : public BaseGraph
{
	Map<std::string, Ville> cities;
	Map<std::string, std::vector<std::string>> roads;

	/// Adds the given city to the graph
	void addCity(const Ville& city);

	/// Adds a one-directional road between two cities with the given names
	void addRoad(const std::string& origin, const std::string& destination);
public:
	/// Gets the amount of cities on the graph
	[[nodiscard]] std::size_t getCityCount() const;

	/// Checks if the graph has a city with the given name
	[[nodiscard]] bool hasCity(const std::string& name) const;

	/// Loads the graph from the given stream
	static CityGraph loadFromStream(std::ifstream& stream);
};


#endif //INC_8INF259_TP2_CITYGRAPH_H
