#pragma once
#include "../../include/ds/Graph.h"

namespace ds
{
	template <typename Node, typename Edge>
	Graph<Node, Edge>::Graph()
	{
		this->nextId = 0;
	}

	template <typename Node, typename Edge>
	Graph<Node, Edge>::~Graph() = default;

	template <typename Node, typename Edge>
	int Graph<Node, Edge>::addNode(Node element)
	{
		const int id = this->nextId;

		this->nodes.insert(id, element);

		++this->nextId;

		return id;
	}

	template <typename Node, typename Edge>
	void Graph<Node, Edge>::addEdge(const int from, const int to, const Edge& edge)
	{
		if (!this->edges.contains(from))
			this->edges.insert(from, {});
		this->edges[from].insert(to, edge);
	}

	template <typename Node, typename Edge>
	const Node& Graph<Node, Edge>::getNode(int id) const
	{
		if (!this->nodes.contains(id))
			throw std::out_of_range("Node with id '" + std::to_string(id) + "' does not exist.");

		return this->nodes.at(id);
	}

	template <typename Node, typename Edge>
	const Set<int>& Graph<Node, Edge>::getNeighbors(const int node) const
	{
		if (this->edges.contains(node))
			return this->edges.at(node);

		static const Set<int> emptySet;
		return emptySet;
	}
}
