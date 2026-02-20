#include "../include/Graph.h"

#include <stdexcept>

Graph::Graph()
{
	this->nodes = {};
	this->links = {};
}

Graph::~Graph() = default;

void Graph::addNode(const std::string& name)
{
	if (this->nodes.contains(name))
		throw std::runtime_error("Node already exists.");

	const auto n = new Node();
	n->name = name;
	
	this->nodes.set(name, n);
}

void Graph::addLink(const std::string& from, const std::string& to)
{
	if (!this->nodes.contains(from) || !this->nodes.contains(to))
		throw std::runtime_error("Node must be added before linking it.");
	
	if (this->links.contains(from))
		this->links.at(from).push_back(to);
	else
		this->links.set(from, {to});
}

size_t Graph::count() const
{
	return this->nodes.size();
}
