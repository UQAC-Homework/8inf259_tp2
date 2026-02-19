#ifndef INC_8INF259_TP2_GRAPH_H
#define INC_8INF259_TP2_GRAPH_H
#include <map>
#include <string>

class Graph
{
	struct Node
	{
		std::string_view name;
	};

	std::map<std::string_view, Node*> nodes;

public:
	Graph();
	~Graph();

	/// Adds a node with the given name
	void addNode(std::string name);

	/// Adds a link between the nodes with the given names
	void addLink(std::string from, std::string to);
};


#endif //INC_8INF259_TP2_GRAPH_H
