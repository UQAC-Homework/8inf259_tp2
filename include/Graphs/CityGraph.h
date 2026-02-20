#ifndef INC_8INF259_TP2_CITYGRAPH_H
#define INC_8INF259_TP2_CITYGRAPH_H
#include "BaseGraph.h"
#include "../Map.h"
#include "../Ville.h"

/// Graph that represents a network of cities
class CityGraph : public BaseGraph<Ville>
{
	Map<std::string, int> nameToId;

public:
	/// Adds a city on the graph
	void addCity(const Ville& city);

	/// Adds a road between the cities with the given names
	void addRoad(const std::string& from, const std::string& to);

	/// Gets the amount of cities on the graph
	[[nodiscard]] std::size_t getCityCount() const;

	/// Loads the graph from the given stream
	static CityGraph loadFromStream(std::ifstream& stream);
};


#endif //INC_8INF259_TP2_CITYGRAPH_H
