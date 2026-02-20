#include "../../include/Graphs/BaseGraph.h"

#include "../../include/Ville.h"


template <typename T>
BaseGraph<T>::BaseGraph()
{
	this->nextId = 0;
}

template <typename T>
BaseGraph<T>::~BaseGraph() = default;

template <typename T>
int BaseGraph<T>::addNode(T element)
{
	const int id = this->nextId;

	this->nodes.insert(id, element);

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

template class BaseGraph<Ville>;