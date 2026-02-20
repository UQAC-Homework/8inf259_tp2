#include "../../include/Graphs/BaseGraph.h"

#include <stdexcept>

BaseGraph::BaseGraph()
{
	this->nextId = 0;
}

int BaseGraph::addNode()
{
	const int id = this->nextId;

	this->nextId++;

	return id;
}

void BaseGraph::addEdge(const int from, const int to)
{
	if (this->edges.contains(from))
		this->edges.at(from).emplace(to);
	else
		this->edges.set(from, {to});
}
