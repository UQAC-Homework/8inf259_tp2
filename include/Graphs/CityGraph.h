#ifndef INC_8INF259_TP2_CITYGRAPH_H
#define INC_8INF259_TP2_CITYGRAPH_H
#include "BaseGraph.h"
#include "../Map.h"
#include "../Ville.h"

/// Graph that represents a network of cities
class CityGraph : public BaseGraph
{
	Map<std::string, Ville> cities;

	/// Adds the given city to the graph
	void addCity(const Ville& city);

public:
	/// Gets the amount of cities on the graph
	[[nodiscard]] std::size_t getCityCount() const;

	/// Loads the graph from the given stream
	static CityGraph loadFromStream(std::ifstream& stream);
};


#endif //INC_8INF259_TP2_CITYGRAPH_H
