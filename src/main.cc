#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include "graph_CSR.hh"
#include "coloring.hh"

int main(int argc, char const *argv[])
{
    // Test 1
    // Small graph
    std::cout << "Test1:" << std::endl;
    int numVertices = 6;
    int numEdges = 5;
    Graph g1(GraphType::undirected, numVertices, numEdges);

    // Setup edges
    g1.addEdge(0,1,4);
    g1.addEdge(3,4);
    g1.addEdge(0,2);
    g1.addEdge(3,1);
    g1.addEdge(5,0);

    g1.randomizeVertexValues();

    for (uint32_t i = 0;  i < g1.sizeVertex(); i++)
    {
        std::cout << g1.getVertexValue(i) << " "; 
    }
    std::cout << std::endl;
    
    naive_coloring(g1);

    for (uint32_t i = 0;  i < g1.sizeVertex(); i++)
    {
        std::cout << g1.getVertexValue(i) << " "; 
    }
    std::cout << std::endl;
    if (assessGraph(g1))
    {
        std::cout << "Test 1 Passed!" << std::endl;
    }
    else
    {
        std::cout << "Test 1 Failed!" << std::endl;
    }



    // Test 2
    // Small complete graph
    std::cout << std::endl;
    std::cout << "Test2:" << std::endl;
    numVertices = 6;
    numEdges = numVertices*(numVertices -1)/2 ; //  n(n − 1)/2
    Graph g2(GraphType::undirected, numVertices, numEdges);

    // Setup edges - fully connected
    for (uint32_t i = 0;  i < g2.sizeVertex(); i++)
    {
        for (uint32_t j = i + 1;  j < g2.sizeVertex(); j++)
        {
            g2.addEdge(i,j);
        }
    }

    g2.randomizeVertexValues();

    for (uint32_t i = 0;  i < g2.sizeVertex(); i++)
    {
        std::cout << g2.getVertexValue(i) << " "; 
    }
    std::cout << std::endl;

    naive_coloring(g2);

    for (uint32_t i = 0;  i < g2.sizeVertex(); i++)
    {
        std::cout << g2.getVertexValue(i) << " "; 
    }
    std::cout << std::endl;
    if (assessGraph(g2))
    {
        std::cout << "Test 2 Passed!" << std::endl;
    }
    else
    {
        std::cout << "Test 2 Failed!" << std::endl;
    }

    // Test 3
    // SNAP facebook data set
    std::cout << std::endl;
    std::cout << "Test3:" << std::endl;

    // Open facebook data
    // Put edges into queue
    // Get number of edges
    std::list<std::pair<uint32_t, uint32_t>> edgeList;
    std::string line;
    std::ifstream facebookDS("datasets/facebook/0.edges");
    uint32_t numLines = 0;
    while (std::getline(facebookDS, line))
    {
        std::stringstream linestream(line);
        std::string data;
        uint32_t val1;
        uint32_t val2;

        linestream >> val1 >> val2;
        std::pair<uint32_t, uint32_t> edge(val1,val2);
        edgeList.push_back(edge);
        numLines++;
    }

    numEdges = numLines;
    Graph g3(GraphType::undirected, numEdges);

    // Add edges in list to graph
    for (auto e = edgeList.begin(); e != edgeList.end(); e++)
    {   
        g3.addEdge(e->first, e->second);
    }
 
    g3.randomizeVertexValues();
    naive_coloring(g3);
    if (assessGraph(g3))
    {
        std::cout << "Test 3 Passed!" << std::endl;
    }
    else
    {
        std::cout << "Test 3 Failed!" << std::endl;
    }

    return 0;
}

