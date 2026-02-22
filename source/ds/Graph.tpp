#pragma once
#include "../../include/ds/Graph.h"

namespace ds
{
	template <typename Node, typename Edge>
	Graph<Node, Edge>::Graph() = default;

	template <typename Node, typename Edge>
	Graph<Node, Edge>::~Graph() = default;

	template <typename Node, typename Edge>
	int Graph<Node, Edge>::addNode(Node value)
	{
		const int id = this->nextId;

		this->nodes.insert(id, value);

		++this->nextId;

		return id;
	}

	template <typename Node, typename Edge>
	const Node& Graph<Node, Edge>::getNode(int id) const
	{
		return this->nodes.at(id);
	}

	template <typename Node, typename Edge>
	void Graph<Node, Edge>::addEdge(int from, int to, const Edge& value)
	{
		if (this->areConnected(from, to))
			throw std::logic_error(
				"An edge between '" + std::to_string(from) + "' and '" + std::to_string(to) + "' already exists.");

		if (!this->edges.contains(from))
			this->edges.insert(from, {});

		this->edges[from].insert(to, value);
	}

	template <typename Node, typename Edge>
	Edge& Graph<Node, Edge>::removeEdge(int from, int to)
	{
		Edge& edge = this->edges[from][to];
		this->edges[from].erase(to);

		return edge;
	}

	template <typename Node, typename Edge>
	bool Graph<Node, Edge>::areConnected(int from, int to) const
	{
		if (!this->edges.contains(from))
			return false;

		return this->edges.at(from).contains(to);
	}

	template <typename Node, typename Edge>
	const Map<int, Edge>& Graph<Node, Edge>::getEdges(int node) const
	{
		if (this->edges.contains(node))
			return this->edges.at(node);

		static const Map<int, Edge> empty;
		return empty;
	}

	template <typename Node, typename Edge>
	std::size_t Graph<Node, Edge>::size() const
	{
		return this->nodes.size();
	}
}
