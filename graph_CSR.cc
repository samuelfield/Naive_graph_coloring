#include <iostream>
#include <random>
#include "graph_CSR.hh"

Graph::Graph(unsigned int numVertices, unsigned int numEdges)
{
    this->numVertices = numVertices;
    this->currentNumEdges = 0;
    this->maxDegree = 0;
    inEdgeIdxs.resize(numVertices + 1);
    vertexValues.resize(numVertices);
    vertexDegree.resize(numVertices);
    srcIndex.resize(numEdges);
    edgeValues.resize(numEdges);

    // Initialize vertex values to their index number
    for (unsigned int i = 0; i < numVertices; i++)
    {
        vertexValues[i] = i;
    }
}

Graph::~Graph()
{
}

void Graph::addEdge(unsigned int startV, unsigned int endV, int weight)
{
    // Insert edge into source index vector and edge values vector
    int insertIndex = inEdgeIdxs[endV+1];
    for (int i = currentNumEdges; i > insertIndex; i--)
    {
        srcIndex[i] = srcIndex[i-1];
        edgeValues[i] = edgeValues[i-1];
    }
    srcIndex[insertIndex] = startV;
    edgeValues[insertIndex] = weight;

    // Change the inEdgeInxs values for vertex labels greater than the end node
    for (unsigned int i = endV+1; i < numVertices + 1; i++)
    {
        inEdgeIdxs[i]++;
    }

    // Increase degree of vertex and check max vertex
    vertexDegree[endV]++;
    if (vertexDegree[endV] > this->maxDegree)
    {
        this->maxDegree = vertexDegree[endV];
    }

    // Increase the value measuring the current number of edges
    currentNumEdges++;
}

void Graph::randomizeVertexValues()
{
    unsigned int maxVertVal = maxDegree + 1;
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(0, maxVertVal);

    for (auto& v : vertexValues)
        v = dist(mt);
}

void Graph::setVertexValue(unsigned int vertex, int value)
{
    vertexValues[vertex] = value;
}

void Graph::printGraph()
{
    std::cout << "\nIn Edge Indexes:" << std::endl;
    for (auto &i : inEdgeIdxs)
    {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    std::cout << "\nVertex Values:" << std::endl;
    for (auto &i : vertexValues)
    {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    std::cout << "\nVertex Degree:" << std::endl;
    for (auto &i : vertexDegree)
    {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    std::cout << "\nSource Indexes:" << std::endl;
    for (auto &i : srcIndex)
    {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    std::cout << "\nEdge Values:" << std::endl;
    for (auto &i : edgeValues)
    {
        std::cout << i << " ";
    }
    std::cout << std::endl;
}