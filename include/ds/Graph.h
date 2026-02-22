#ifndef INC_8INF259_TP2_GRAPH_H
#define INC_8INF259_TP2_GRAPH_H
#include "Map.h"

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

		/// Adds a node to the graph 
		int addNode(Node value);

		/// Gets the value of the given node
		const Node& getNode(int id) const;

		/// Adds an edge between the given nodes
		void addEdge(int from, int to, const Edge& value);

		/// Removes the edge between the given nodes
		Edge& removeEdge(int from, int to);

		/// Checks if the given nodes are connected
		[[nodiscard]] bool areConnected(int from, int to) const;

		/// Gets the edges connected to the given node
		[[nodiscard]] const Map<int, Edge>& getEdges(int node) const;

		/// Gets the amount of nodes on the graph
		[[nodiscard]] std::size_t size() const;
	};
}

#include "../../source/ds/Graph.tpp"

#endif //INC_8INF259_TP2_GRAPH_H
