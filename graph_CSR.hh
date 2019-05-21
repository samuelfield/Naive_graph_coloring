#include <vector>

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

class Graph
{
private:
    unsigned int numVertices;
    unsigned int currentNumEdges;
    std::vector<int> inEdgeIdxs;
    std::vector<int> vertexValues;
    std::vector<int> srcIndex;
    std::vector<int>::iterator srcIndexIt;
    std::vector<int> edgeValues;
    std::vector<int>::iterator edgeValuesIt;
    void insertEdge(std::vector<int> edgeVector, int value, unsigned int insertIndex);
public:
    Graph(unsigned int numVertices, unsigned int numEdges);
    ~Graph();
    void addEdge(unsigned int startV, unsigned int endV, int weight = 0);
    void setVertexValue(unsigned int vertex, int value);
    // void printGraph();
};