#include <iostream>
#include <vector>
#include "graph.hh"

// Edge Functions
Edge::Edge(int endNode, int weight)
{
    this->weight = weight;
    this->endNode = endNode;
}

int Edge::getEndNode()
{
    return endNode;
}

// Vertex Functions
Vertex::Vertex(int value = 0)
{
    this->value = value;
}

void Vertex::addEdge(int endNode, int weight)
{
    neighbors.push_back(Edge(endNode, weight));
}

void Vertex::setValue(int value)
{
    this->value = value;
}

Edge* Vertex::searchEdges(int endNode)
{
    for (edge_i = neighbors.begin(); edge_i != neighbors.end(); edge_i++)
    {
        if (edge_i->getEndNode() == endNode)
        {
            return &(*edge_i);
        }
    }

    return NULL;    
}

// Graph functions 
Graph::Graph()
{
    graph.resize(8);
}

void Graph::addEdge(unsigned int startNode, unsigned int endNode, int weight)
{
    unsigned int maxNodeVal = std::max(startNode, endNode);

    if (graph.size() < maxNodeVal)
    {
        graph.resize(maxNodeVal * 2);
    }

    if(checkDuplicate(startNode, endNode))
    {
        std::cout << "Edge (" << startNode << "," << endNode << ") already exists!\n";
    }

    graph[startNode].addEdge(endNode);
}

void Graph::setVertexValue(unsigned int vertex, int value)
{
    if (graph.size() < vertex)
    {
        std::cout << "Vertex not implemented\n";
        return;
    }

    graph[vertex].setValue(value);
}

bool Graph::checkDuplicate(unsigned int startNode, unsigned int endNode)
{
    if (graph[startNode].searchEdges(endNode) != NULL)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Graph::printGraph()
{
    std::cout << graph.size() << "\n";
}