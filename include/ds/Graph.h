#ifndef INC_8INF259_TP2_GRAPH_H
#define INC_8INF259_TP2_GRAPH_H
#include <set>
#include <unordered_map>

namespace ds
{
	template <typename Node>
	class Graph
	{
		int nextId;
		std::unordered_map<int, std::set<int>> edges;
		std::unordered_map<int, Node> nodes;

	public:
		Graph();
		~Graph();

		/// Adds a node to the graph 
		int addNode(Node value);

		/// Gets the value of the given node
		[[nodiscard]] const Node& getNode(int id) const;

		/// Gets the value of the given node
		[[nodiscard]] Node& getNode(int id);

		/// Adds an edge between the given nodes
		void addEdge(int from, int to);

		/// Removes the edge between the given nodes
		void removeEdge(int from, int to);

		/// Checks if the given nodes are connected
		[[nodiscard]] bool areConnected(int from, int to) const;

		/// Gets the edges connected to the given node
		[[nodiscard]] const std::set<int>& getEdges(int node) const;

		/// Gets the amount of nodes on the graph
		[[nodiscard]] std::size_t size() const;
	};
}

#include "../../source/ds/Graph.tpp"

#endif //INC_8INF259_TP2_GRAPH_H
