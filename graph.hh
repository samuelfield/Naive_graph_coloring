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
    int name;
    int value;
    std::vector<Edge> neighbors;
    std::vector<Edge>::iterator edge_i;
public:
    Vertex(int value);
    void addEdge(unsigned int endNode, int weight = 0);
    void setValue(int value);
    void setName(int name);
    int getValue();
    int getName();
    Edge* searchEdges(int endNode);
    void printNeighbors();
};

class Graph
{
private:
    std::vector<Vertex> graph;
    std::vector<Vertex>::iterator vertex_i;
public:
    Graph();
    void addEdge(unsigned int startNode, unsigned int endNode, int weight = 0);
    void setVertexValue(unsigned int vertex, int value);
    bool checkDuplicate(unsigned int startNode, unsigned int endNode);
    void printGraph();
};