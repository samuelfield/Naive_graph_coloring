#include <vector>

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
    int value;
    std::vector<Edge> neighbors;
    std::vector<Edge>::iterator edge_i;
public:
    Vertex(int value);
    void addEdge(int endNode, int weight = 0);
    void setValue(int value);
    Edge* searchEdges(int endNode);
};

class Graph
{
private:
    std::vector<Vertex> graph;
    std::vector<Vertex>::const_iterator vertex_i;
public:
    Graph();
    void addEdge(unsigned int startNode, unsigned int endNode, int weight = 0);
    void setVertexValue(unsigned int vertex, int value);
    bool checkDuplicate(unsigned int startNode, unsigned int endNode);
    void printGraph();
};