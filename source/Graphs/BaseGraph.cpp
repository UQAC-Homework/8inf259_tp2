#include "../../include/Graphs/BaseGraph.h"


template <typename T>
BaseGraph<T>::BaseGraph()
{
	this->nextId = 0;
}

template <typename T>
int BaseGraph<T>::addNode(T element)
{
	const int id = this->nextId;

	this->nodes.emplace(id, element);

	++this->nextId;

	return id;
}

template <typename T>
void BaseGraph<T>::addEdge(const int from, const int to)
{
	if (!this->edges.contains(from))
		this->edges.insert(from, {});
	this->edges[from].insert(to);
}
