#pragma once
#include <stdexcept>

#include "../../include/ds/Graph.h"

namespace ds
{
	template <typename Node>
	Graph<Node>::Graph()
	{
		this->nextId = 0;
	}

	template <typename Node>
	Graph<Node>::~Graph() = default;

	template <typename Node>
	int Graph<Node>::addNode(Node value)
	{
		const auto id = this->nextId;

		this->nodes[id] = value;

		++this->nextId;

		return id;
	}

	template <typename Node>
	const Node& Graph<Node>::getNode(int id) const
	{
		return this->nodes.at(id);
	}

	template <typename Node>
	Node& Graph<Node>::getNode(int id)
	{
		return this->nodes[id];
	}

	template <typename Node>
	void Graph<Node>::addEdge(int from, int to)
	{
		if (this->areConnected(from, to))
			throw std::logic_error(
				"An edge between '" + std::to_string(from) + "' and '" + std::to_string(to) + "' already exists.");

		if (!this->edges.contains(from))
			this->edges[from] = {};

		this->edges[from].insert(to);
	}

	template <typename Node>
	void Graph<Node>::removeEdge(int from, int to)
	{
		this->edges[from].erase(to);
	}

	template <typename Node>
	bool Graph<Node>::areConnected(const int from, const int to) const
	{
		if (!this->edges.contains(from))
			return false;

		return this->edges.at(from).contains(to);
	}

	template <typename Node>
	const std::set<int>& Graph<Node>::getEdges(const int node) const
	{
		if (this->edges.contains(node))
			return this->edges.at(node);

		static const std::set<int> empty;
		return empty;
	}

	template <typename Node>
	std::size_t Graph<Node>::size() const
	{
		return this->nodes.size();
	}
}
