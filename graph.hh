#include <vector>

class Edge
{
private:
    int weight;
    int startNode;
    int endNode;
public:
    Edge(int startNode, int endNode);
    ~Edge();
};


class AdjacencyList
{
private:
    std::vector<Edge*> edges;
public:
    AdjacencyList(int size);
    ~AdjacencyList();
};

class Graph
{
private:
    AdjacencyList* graph;
public:
    Graph(int size);
    ~Graph();
};