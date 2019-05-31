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

    for (uint32_t i = 0;  i < g.sizeVertex(); i++)
    {
        std::cout << g.getVertexValue(i) << " "; 
    }
    std::cout << std::endl;
    std::cout << std::endl;

    naive_coloring(g);

    if (assessGraph(g))
    {
        std::cout << "Graph Accectable:" << std::endl;
    }
    else
    {
        std::cout << "ERROR!:" << std::endl;
    }
    
    for (uint32_t i = 0;  i < g.sizeVertex(); i++)
    {
        std::cout << g.getVertexValue(i) << " "; 
    }
    std::cout << std::endl;

    return 0;
}

