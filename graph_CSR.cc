#include <iostream>
#include <vector>
#include "graph_CSR.hh"

// // private:
//     std::vector<int> inEdgeIdxs;
//     std::vector<int> vertexValues;
//     std::vector<int> srcIndex;
//     std::vector<int>::iterator srcIndexIt;
//     std::vector<int> edgeValues;
//     std::vector<int>::iterator edgeValuesIt;

Graph::Graph(unsigned int numVertices, unsigned int numEdges)
{
    this->numVertices = numVertices;
    this->currentNumEdges = 0;
    inEdgeIdxs.resize(numVertices + 1);
    vertexValues.resize(numVertices);
    srcIndex.resize(numEdges);
    edgeValues.resize(numEdges);
}

Graph::~Graph()
{
}

void Graph::addEdge(unsigned int startV, unsigned int endV, int weight)
{
    int insertIndex = inEdgeIdxs[endV+1];
    insertEdge(srcIndex, startV, insertIndex);
    insertEdge(edgeValues, weight, insertIndex);
    
    // Change the inEdgeInxs values for vertex labels greater than the end node
    for (unsigned int i = endV+1; i < numVertices; i++)
    {
        inEdgeIdxs[i]++;
    }

    // Increase the value measuring the current number of edges
    currentNumEdges++;
}

void Graph::insertEdge(std::vector<int> edgeVector, int value, unsigned int insertIndex)
{
    for (unsigned int i = currentNumEdges; i > insertIndex; i--)
    {
        edgeVector[i] = edgeVector[i-1];
    }
    edgeVector[insertIndex] = value;
}

void Graph::setVertexValue(unsigned int vertex, int value)
{
    vertexValues[vertex] = value;
}

// void Graph::printGraph()
// {
//     std::cout << "\nGraph (adjacency list form):\n";
//     for (vertex_i = graph.begin(); vertex_i != graph.end(); vertex_i++)
//     {
//         Vertex* v  = *vertex_i;
//         if (v != NULL)
//         {
//             std::cout << v->getName() << " - ";
//             v->printNeighbors();
//         }
//     }
// }