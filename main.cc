#include <iostream>
#include "graph.hh"

int main(int argc, char const *argv[])
{
    Graph g;

    g.addEdge(1,2,4);
    g.addEdge(2,1);
    g.addEdge(4,5);
    g.addEdge(1,3);
    g.addEdge(4,2);
    g.addEdge(6,1);
    g.addEdge(4,5);

    return 0;
}

