#ifndef INC_8INF259_TP2_GRAPH_H
#define INC_8INF259_TP2_GRAPH_H
#include "Map.h"
#include "Set.h"

namespace ds
{
	template <typename Node, typename Edge>
	class Graph
	{
		int nextId;
		Map<int, Map<int, Edge>> edges;
		Map<int, Node> nodes;

	public:
		Graph();
		~Graph();

		/// Adds a new node onto the graph
		int addNode(Node element);

		/// Adds an edge between two nodes with the given ids
		void addEdge(int from, int to);

		/// Gets the node with the given id
		const Node& getNode(int id) const;

		/// Gets the nodes sharing an edge with the given node
		[[nodiscard]] const Set<int>& getNeighbors(int node) const;
	};
}

#include "../../source/ds/Graph.tpp"

#endif //INC_8INF259_TP2_GRAPH_H
