#include <iostream>
#include "graph_CSR.hh"
#include "coloring.hh"

int main(int argc, char const *argv[])
{
    int numVertices = 6;
    int numEdges = 5;
    Graph g(GraphType::undirected, numVertices, numEdges);

    g.addEdge(0,1,4);
    g.addEdge(3,4);
    g.addEdge(0,2);
    g.addEdge(3,1);
    g.addEdge(5,0);

    g.randomizeVertexValues();
    g.printGraph();

    naive_coloring(g);

    g.printGraph();

    return 0;
}

