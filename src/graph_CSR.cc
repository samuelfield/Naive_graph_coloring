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

Graph::Graph(GraphType gType, uint32_t numEdges)
{
    this->gType = gType;
    this->numVertices = 1;
    this->currentNumEdges = 0;
    this->maxDegree = 0;

    // Resize vertex vectors to minimum size (1)
    inEdgeIdxs.resize(this->numVertices + 1);
    vertexValues.resize(this->numVertices);
    vertexDegree.resize(this->numVertices);

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
}

Graph::~Graph()
{
}

uint32_t Graph::sizeVertex()
{
    return numVertices;
}

uint32_t Graph::sizeEdges()
{
    return currentNumEdges;
}

uint32_t Graph::getMaxDeg()
{
    return maxDegree;
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
    // Add vertex if not already present and increase numVertices
    uint32_t maxVertexID = std::max(startV, endV);
    uint32_t reqNumVertices = maxVertexID + 1;
    uint32_t oldNumVertices = this->numVertices;
    if (oldNumVertices < reqNumVertices)
    {
        uint32_t fill_InEdgeIndex = inEdgeIdxs[oldNumVertices];
        this->numVertices = reqNumVertices;
        inEdgeIdxs.resize(this->numVertices + 1);
        vertexValues.resize(this->numVertices);
        vertexDegree.resize(this->numVertices);

        // Fill the in edge index vector with previous last value
        for (uint32_t i = oldNumVertices; i < this->numVertices + 1; i++)
        {
            // std::cout << i << std::endl;
            inEdgeIdxs[i] = fill_InEdgeIndex;
        }
    }

    // Insert edge into source index vector and edge values vector
    uint32_t insertIndex = inEdgeIdxs[endV+1];
    for (uint32_t i = this->currentNumEdges; i > insertIndex; i--)
    {
        srcIndex[i] = srcIndex[i-1];
        edgeValues[i] = edgeValues[i-1];
    }
    srcIndex[insertIndex] = startV;
    edgeValues[insertIndex] = weight;

    // Change the inEdgeInxs values for vertex labels greater than the end node
    for (uint32_t i = endV+1; i < numVertices + 1; i++)
    {
        this->inEdgeIdxs[i]++;
    }

    // Increase degree of vertex
    vertexDegree[endV]++;
    if (vertexDegree[endV] > maxDegree)
    {
        this->maxDegree = vertexDegree[endV];
    }

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
    uint32_t maxVertVal = this->maxDegree;
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

int32_t Graph::getVertexValue(uint32_t vertex)
{
    return vertexValues[vertex];
}

int32_t* Graph::getVertexValueAddress(uint32_t vertex)
{
    return &vertexValues[vertex];
}

uint32_t Graph::getNeighbors(std::vector<int>& neighbors, uint32_t vertex)
{
    uint32_t vDegree = vertexDegree[vertex]; 
    neighbors.resize(vDegree);
    copyNeighbours(neighbors, vertex);

    return vDegree;
}

void Graph::copyNeighbours(std::vector<int>& neighbors, uint32_t vertex)
{
    for (uint32_t i = inEdgeIdxs[vertex]; i < inEdgeIdxs[vertex+1]; i++)
    {
        uint32_t n_i = i - inEdgeIdxs[vertex];
        neighbors[n_i] = srcIndex[i];
    }
}

void Graph::printGraph()
{
    if (this->gType == GraphType::directed)
    {
        std::cout << "\n\nGraph Type: Directed" << std::endl;
    }
    else
    {
        std::cout << "\n\nGraph Type: Undirected" << std::endl;
    }
    
    std::cout << "In Edge Indexes:" << std::endl;
    for (auto &i : inEdgeIdxs)
    {
        std::cout << i << " ";
    }

    std::cout << "\nVertex Values:" << std::endl;
    for (auto &i : vertexValues)
    {
        std::cout << i << " ";
    }

    std::cout << "\nVertex Degree:" << std::endl;
    for (auto &i : vertexDegree)
    {
        std::cout << i << " ";
    }

    std::cout << "\nSource Indexes:" << std::endl;
    for (auto &i : srcIndex)
    {
        std::cout << i << " ";
    }

    std::cout << "\nEdge Values:" << std::endl;
    for (auto &i : edgeValues)
    {
        std::cout << i << " ";
    }
    std::cout << std::endl;
}