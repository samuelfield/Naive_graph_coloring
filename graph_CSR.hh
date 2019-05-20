#include <vector>

/* Graph data structure */
/*
* Assumes that if there are N vertices in the graph then the vertex labels
* are continuous from 0 to N-1 (i.e. there are no gaps in naming).
*
* Possible TODO: Create function that maps graph input data to vertex names
*/

class Edge
{
private:
    int weight;
    int endNode;
public:
    Edge(int endNode, int weight = 0);
    int getEndNode();
};


class Vertex
{
private:
    int name;
    int value;
    std::vector<Edge*> neighbors;
    std::vector<Edge*>::iterator edge_i;
public:
    Vertex(int name, int value = 0);
    ~Vertex();
    void addEdge(unsigned int endNode, int weight = 0);
    void setValue(int value);
    int getValue();
    int getName();
    Edge* searchEdges(int endNode);
    void printNeighbors();
};

class Graph
{
private:
    std::vector<Vertex*> graph;
    std::vector<Vertex*>::iterator vertex_i;

    // CSR format
    std::vector<int> inEdgeIdxs;
    std::vector<int> srcIndex;
    std::vector<int> vertexValues;
    std::vector<int> edgeValues;
public:
    Graph(int numVertices);
    ~Graph();
    void addEdge(unsigned int startNode, unsigned int endNode, int weight = 0);
    void addVertex(unsigned int startNode, unsigned int endNode, int value = 0);
    void setVertexValue(unsigned int vertex, int value);
    bool checkDuplicate(unsigned int startNode, unsigned int endNode);
    void printGraph();
};