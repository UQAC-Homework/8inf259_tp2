#ifndef INC_8INF259_TP2_CITYGRAPH_H
#define INC_8INF259_TP2_CITYGRAPH_H
#include "BaseGraph.h"
#include "../Ville.h"

/// Graph that represents a network of cities
class CityGraph : public BaseGraph
{
public:
	/// Loads the graph from the given stream
	static CityGraph loadFromStream(std::ifstream& stream);
};


#endif //INC_8INF259_TP2_CITYGRAPH_H