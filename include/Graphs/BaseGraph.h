#ifndef INC_8INF259_TP2_BASEGRAPH_H
#define INC_8INF259_TP2_BASEGRAPH_H

#include "../Map.h"
#include "../Set.h"

/// Class that represents a graph of any kind
template <typename T>
class BaseGraph
{
	int nextId;
	Map<int, Set<int>> edges;
	Map<int, T> nodes;

protected:
	BaseGraph();
	~BaseGraph();

	/// Adds a new node onto the graph
	int addNode(T element);

	/// Adds an edge between two nodes with the given ids
	void addEdge(int from, int to);

	/// Gets the node with the given id
	const T& getNode(int id) const;
};


#endif //INC_8INF259_TP2_BASEGRAPH_H
