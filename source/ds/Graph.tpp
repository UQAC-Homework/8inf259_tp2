#pragma once
#include <stdexcept>

#include "../../include/ds/Graph.h"

namespace ds
{
	template <typename Node>
	Graph<Node>::Graph()
	{
		this->_nextId = 0;
	}

	template <typename Node>
	Graph<Node>::~Graph() = default;

	template <typename Node>
	int Graph<Node>::addNode(Node value)
	{
		const auto id = this->_nextId;

		this->_nodes[id] = value;

		++this->_nextId;

		return id;
	}

	template <typename Node>
	const Node& Graph<Node>::getNode(int id) const
	{
		return this->_nodes.at(id);
	}

	template <typename Node>
	Node& Graph<Node>::getNode(int id)
	{
		return this->_nodes[id];
	}

	template <typename Node>
	void Graph<Node>::addEdge(int from, int to)
	{
		if (this->hasEdge(from, to))
			throw std::logic_error(
				"An edge between '" + std::to_string(from) + "' and '" + std::to_string(to) + "' already exists.");

		if (!this->_edges.contains(from))
			this->_edges[from] = {};

		this->_edges[from].insert(to);
	}

	template <typename Node>
	void Graph<Node>::removeEdge(int from, int to)
	{
		this->_edges[from].erase(to);
	}

	template <typename Node>
	bool Graph<Node>::hasEdge(const int from, const int to) const
	{
		if (!this->_edges.contains(from))
			return false;

		return this->_edges.at(from).contains(to);
	}

	template <typename Node>
	const std::set<int>& Graph<Node>::getEdges(const int node) const
	{
		if (this->_edges.contains(node))
			return this->_edges.at(node);

		static const std::set<int> EMPTY;
		return EMPTY;
	}

	template <typename Node>
	std::size_t Graph<Node>::size() const
	{
		return this->_nodes.size();
	}
}
