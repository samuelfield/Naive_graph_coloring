#include <vector>
#include "graph.hh"

Edge::Edge(int startNode, int endNode)
{
    weight = 0;
    this->startNode = startNode;
    this->endNode = endNode;
}

Edge::~Edge()
{
}

AdjacencyList::AdjacencyList(int size)
{
    edges.resize(size);
}

AdjacencyList::~AdjacencyList()
{
}

Graph::Graph(int size)
{
    graph = new AdjacencyList(size);
}

Graph::~Graph()
{
}
