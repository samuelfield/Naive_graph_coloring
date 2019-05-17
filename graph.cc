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
    name = 0;
    this->value = value;
}

void Vertex::addEdge(unsigned int endNode, int weight)
{ 
    neighbors.push_back(Edge(endNode, weight));
}

void Vertex::setValue(int value)
{
    this->value = value;
}

void Vertex::setName(int name)
{
    this->name = name;
}

int Vertex::getValue()
{
    return value;
}

int Vertex::getName()
{
    return name;
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

void Vertex::printNeighbors()
{
    for (edge_i = neighbors.begin(); edge_i != neighbors.end(); edge_i++)
    {
        std::cout << edge_i->getEndNode() << " ";
    }

    std::cout << "\n";
}

// Graph functions 
Graph::Graph()
{
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

    graph[startNode].setName(startNode);
    graph[startNode].addEdge(endNode, weight);
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
    for (vertex_i = graph.begin(); vertex_i != graph.end(); vertex_i++)
    {
        std::cout << vertex_i->getName() << " - ";
        vertex_i->printNeighbors();
    }
}