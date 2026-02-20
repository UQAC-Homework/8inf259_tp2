#ifndef INC_8INF259_TP2_GRAPH_H
#define INC_8INF259_TP2_GRAPH_H
#include <string>
#include <vector>

#include "Map.h"

class Graph
{
	struct Node
	{
		std::string name;
	};

	Map<std::string, Node*> nodes;
	Map<std::string, std::vector<std::string>> links;

public:
	Graph();
	~Graph();

	/// Adds a node with the given name
	void addNode(const std::string& name);

	/// Adds a one-directional link between the nodes with the given names
	void addLink(const std::string& from, const std::string& to);

	/// Gets the number of nodes added
	[[nodiscard]] size_t count() const;
};


#endif //INC_8INF259_TP2_GRAPH_H
