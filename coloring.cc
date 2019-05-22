#include <iostream>
#include <thread>
#include "coloring.hh"

// Boman coloring implementation
void boman_coloring(Graph& graph)
{
    partition(graph);
}

void partition(Graph& graph)
{
    unsigned int nthreads = std::thread::hardware_concurrency();
}