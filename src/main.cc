#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include "graph_CSR.hh"
#include "coloring.hh"

// Todo: Get Reader working from graph.h / io.h


// Test 1
// Small graph
void Test1()
{
    std::cout << "*********\nTest1:\n*********" << std::endl;
    uint32_t numVertices = 6;
    uint32_t numEdges = 5;
    Graph g1(GraphType::undirected, numVertices, numEdges);

    // Setup edges
    g1.addEdge(0,1,4);
    g1.addEdge(3,4);
    g1.addEdge(0,2);
    g1.addEdge(3,1);
    g1.addEdge(5,0);

    g1.randomizeVertexValues();
    g1.printGraph();

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
}


// Test 2.1
// Small complete graph
void Test2_1()
{
    std::cout << "*********\nTest2_1:\n*********" << std::endl;
    uint32_t numVertices = 6;
    uint32_t numEdges = numVertices*(numVertices -1)/2 ; //  n(n − 1)/2
    Graph g2_1(GraphType::undirected, numVertices, numEdges);

    // Setup edges - fully connected
    for (uint32_t i = 0;  i < g2_1.sizeVertex(); i++)
    {
        for (uint32_t j = i + 1;  j < g2_1.sizeVertex(); j++)
        {
            g2_1.addEdge(i,j);
        }
    }

    g2_1.randomizeVertexValues();
    // g2_1.printGraph();

    std::cout << "Initial values: "; 
    for (uint32_t i = 0;  i < g2_1.sizeVertex(); i++)
    {
        std::cout << g2_1.getVertexValue(i) << " "; 
    }
    std::cout << std::endl;

    naive_coloring(g2_1);

    std::cout << "\nFinal values: "; 
    for (uint32_t i = 0;  i < g2_1.sizeVertex(); i++)
    {
        std::cout << g2_1.getVertexValue(i) << " "; 
    }
    std::cout << std::endl;
    if (assessGraph(g2_1))
    {
        std::cout << "Test 2_1 Passed!" << std::endl;
    }
    else
    {
        std::cout << "Test 2_1 Failed!" << std::endl;
    }
}

// Test 2.2
// Small complete graph using edges to construct
void Test2_2()
{
    std::cout << std::endl;
    std::cout << "*********\nTest 2_2:\n*********" << std::endl;
    uint32_t numVertices = 6;
    uint32_t numEdges = numVertices*(numVertices -1)/2 ; //  n(n − 1)/2
    Graph g2_2(GraphType::undirected, numEdges);

    // Setup edges - fully connected
    for (uint32_t i = 0;  i < numVertices; i++)
    {
        for (uint32_t j = i + 1;  j < numVertices; j++)
        {
            g2_2.addEdge(i,j);
        }
    }

    g2_2.randomizeVertexValues();
    // g2_2.printGraph();

    for (uint32_t i = 0;  i < g2_2.sizeVertex(); i++)
    {
        std::cout << g2_2.getVertexValue(i) << " "; 
    }
    std::cout << std::endl;

    naive_coloring(g2_2);

    for (uint32_t i = 0;  i < g2_2.sizeVertex(); i++)
    {
        std::cout << g2_2.getVertexValue(i) << " "; 
    }
    std::cout << std::endl;
    if (assessGraph(g2_2))
    {
        std::cout << "Test 2-2 Passed!" << std::endl;
    }
    else
    {
        std::cout << "Test 2-2 Failed!" << std::endl;
    }
}

// Test 3
// SNAP facebook data set
void Test3()
{
    std::cout << std::endl;
    std::cout << "*********\nTest3:\n*********" << std::endl;

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

    uint32_t numEdges = numLines;
    Graph g3(GraphType::undirected, numEdges);

    // Add edges in list to graph
    for (auto e = edgeList.begin(); e != edgeList.end(); e++)
    {   
        g3.addEdge(e->first, e->second);
    }
 
    g3.randomizeVertexValues();

    for (uint32_t i = 0;  i < g3.sizeVertex(); i++)
    {
        std::cout << g3.getVertexValue(i) << " "; 
    }
    std::cout << std::endl;
    std::cout << std::endl;

    naive_coloring(g3);

    for (uint32_t i = 0;  i < g3.sizeVertex(); i++)
    {
        std::cout << g3.getVertexValue(i) << " "; 
    }
    std::cout << std::endl;

    if (assessGraph(g3))
    {
        std::cout << "Test 3 Passed!" << std::endl;
    }
    else
    {
        std::cout << "Test 3 Failed!" << std::endl;
    }
}

int main(int argc, char const *argv[])
{
    Test1();
    Test2_1();
    Test2_2();
    Test3();

    return 0;
}