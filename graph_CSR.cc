#include <iostream>
#include <random>
#include <algorithm>
#include "graph_CSR.hh"

Graph::Graph(GraphType gType, uint32_t numVertices, uint32_t numEdges)
{
    this->gType = gType;
    this->numVertices = numVertices;
    this->currentNumEdges = 0;
    this->maxDegree = 0;

    // Resize vertex vectors to hold assigned number of vectors
    inEdgeIdxs.resize(numVertices + 1);
    vertexValues.resize(numVertices);
    vertexDegree.resize(numVertices);

    // Resize edge vectors to number of edges based on graph type (undirected 
    // or directed)
    switch(this->gType)
    {
    case GraphType::directed:
        srcIndex.resize(numEdges);
        edgeValues.resize(numEdges);
        break;
    case GraphType::undirected:
        srcIndex.resize(2 * numEdges);
        edgeValues.resize(2 * numEdges);
        break;
    }

    // Initialize vertex values to their index number
    for (uint32_t i = 0; i < numVertices; i++)
    {
        vertexValues[i] = i;
    }
}

Graph::~Graph()
{
}

uint32_t Graph::sizeNodes()
{
    return numVertices;
}

uint32_t Graph::sizeEdges()
{
    return currentNumEdges;
}

void Graph::addEdge(uint32_t startV, uint32_t endV, int weight)
{
    switch(this->gType)
    {
    case GraphType::directed:
        addDirectedEdge(startV, endV, weight);
        break;
    case GraphType::undirected:
        addUndirectedEdge(startV, endV, weight);
        break;
    }
}

void Graph::addDirectedEdge(uint32_t startV, uint32_t endV, int weight)
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
    for (uint32_t i = endV+1; i < numVertices + 1; i++)
    {
        inEdgeIdxs[i]++;
    }

    // Increase degree of vertex
    vertexDegree[endV]++;

    // Increase the value measuring the current number of edges
    currentNumEdges++;
}

void Graph::addUndirectedEdge(uint32_t startV, uint32_t endV, int weight)
{
    addDirectedEdge(startV, endV, weight);
    addDirectedEdge(endV, startV, weight);
}

void Graph::randomizeVertexValues()
{
    uint32_t maxVertVal = *std::max_element(vertexDegree.begin(), vertexDegree.end());
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(0, maxVertVal);

    for (auto& v : vertexValues)
    {
        v = dist(mt);
    }
}

void Graph::setVertexValue(uint32_t vertex, int value)
{
    vertexValues[vertex] = value;
}

int Graph::getVertexValue(uint32_t vertex)
{
    return vertexValues[vertex];
}

void Graph::getNeighbors(std::vector<int>& neighbors, uint32_t vertex)
{
    neighbors.resize(vertexDegree[vertex]);
    auto startIter = srcIndex.begin() + inEdgeIdxs[vertex];
    auto endIter = startIter + inEdgeIdxs[vertex+1];
    std::copy(startIter, endIter, neighbors.begin());
}

void Graph::printGraph()
{
    if (this->gType == GraphType::directed)
    {
        std::cout << "Graph Type: Directed" << std::endl;
    }
    else
    {
        std::cout << "Graph Type: Undirected" << std::endl;
    }
    
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