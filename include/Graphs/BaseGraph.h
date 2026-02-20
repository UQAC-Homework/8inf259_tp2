#ifndef INC_8INF259_TP2_BASEGRAPH_H
#define INC_8INF259_TP2_BASEGRAPH_H
#include <set>

#include "../Map.h"

/// Class that represents a graph of any kind
template <typename T>
class BaseGraph
{
	int nextId;
	Map<int, std::set<int>> edges;
	Map<int, T> nodes;

protected:
	BaseGraph();

	/// Adds a new node onto the graph
	int addNode(T element);

	/// Adds an edge between two nodes with the given ids
	void addEdge(int from, int to);
};


#endif //INC_8INF259_TP2_BASEGRAPH_H
