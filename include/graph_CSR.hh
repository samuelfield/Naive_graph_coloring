#include <vector>
#include <inttypes.h>

#ifndef GRAPH_CSR_H
#define GRAPH_CSR_H

/* Graph data structure */

/*
* Assumptions:
* - Number of vertices and edges are known in advance
* - If there are N vertices in the graph then the vertex labels are continuous
*   from 0 to N-1 (i.e. there are no gaps in naming).
* - There are no duplicate edges or duplicates don't matter
*
* Possible TODO: Create function that maps graph input data to vertex names
*/

enum class GraphType
{
    directed,
    undirected
};

class Graph
{
private:
    GraphType gType;
    uint32_t numVertices;
    uint32_t currentNumEdges;
    uint32_t maxDegree;
    std::vector<uint32_t> inEdgeIdxs;
    std::vector<int> vertexValues;
    std::vector<uint32_t> vertexDegree;
    std::vector<uint32_t> srcIndex;
    std::vector<int> edgeValues;
    
    void addDirectedEdge(uint32_t startV, uint32_t endV, int weight);
    void addUndirectedEdge(uint32_t startV, uint32_t endV, int weight);
    void copyNeighbours(std::vector<int>& neighbors, uint32_t vertex);
public:
    Graph(GraphType gType, uint32_t numVertices, uint32_t numEdges);
    ~Graph();
    uint32_t sizeVertex();
    uint32_t sizeEdges();
    uint32_t getMaxDeg();
    void addEdge(uint32_t startV, uint32_t endV, int weight = 1);
    void randomizeVertexValues();
    void setVertexValue(uint32_t vertex, int value);
    int32_t getVertexValue(uint32_t vertex);
    int32_t* getVertexValueAddress(uint32_t vertex);
    uint32_t getNeighbors(std::vector<int>& neighbors, uint32_t vertex);
    void printGraph();
};

#endif