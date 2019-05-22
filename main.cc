#include <iostream>
#include "graph_CSR.hh"
#include "coloring.hh"

int main(int argc, char const *argv[])
{
    Graph g(6,6);

    g.addEdge(0,1,4);
    g.addEdge(1,0);
    g.addEdge(3,4);
    g.addEdge(0,2);
    g.addEdge(3,1);
    g.addEdge(5,0);

    g.randomizeVertexValues();
    g.printGraph();

    boman_coloring(&g);

    return 0;
}

