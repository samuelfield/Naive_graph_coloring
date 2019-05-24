#include <iostream>
#include <thread>
#include <cilk/cilk.h>
#include "coloring.hh"

// Boman coloring implementation
void boman_coloring(Graph& graph)
{
}

void naive_coloring(Graph& graph)
{
    std::vector<int> neighbors;
    graph.getNeighbors(neighbors, 0);

}