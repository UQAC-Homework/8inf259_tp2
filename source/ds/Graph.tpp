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
	const Node& Graph<Node, Edge>::getNode(int id) const
	{
		if (!this->nodes.contains(id))
			throw std::out_of_range("Node with id '" + std::to_string(id) + "' does not exist.");

		return this->nodes.at(id);
	}

	template <typename Node, typename Edge>
	void Graph<Node, Edge>::addEdge(const int from, const int to, const Edge& edge)
	{
		if (this->isConnected(from, to))
			throw std::logic_error(
				"An edge between '" + std::to_string(from) + "' and '" + std::to_string(to) + "' already exists.");

		if (!this->edges.contains(from))
			this->edges.insert(from, {});

		this->edges[from][to] = edge;
	}

	template <typename Node, typename Edge>
	void Graph<Node, Edge>::removeEdge(const int from, const int to)
	{
		if (!this->isConnected(from, to))
			return;

		auto fromEdges = this->edges.at(from);

		fromEdges.erase(to);

		if (fromEdges.size() == 0)
			this->edges.erase(from);
	}

	template <typename Node, typename Edge>
	const Edge& Graph<Node, Edge>::getEdge(int from, int to) const
	{
		if (!this->isConnected(from, to))
			throw std::out_of_range(
				"No edge defined coming from '" + std::to_string(from) + "' to '" + std::to_string(to) + "'.");

		return this->edges.at(from).at(to);
	}

	template <typename Node, typename Edge>
	const Map<int, Edge>& Graph<Node, Edge>::getNeighbors(const int node) const
	{
		if (this->edges.contains(node))
			return this->edges.at(node);

		static const Map<int, Edge> empty;
		return empty;
	}

	template <typename Node, typename Edge>
	bool Graph<Node, Edge>::isConnected(int from, int to) const
	{
		if (!this->edges.contains(from))
			return false;

		if (!this->edges.at(from).contains(to))
			return false;

		return true;
	}
}
