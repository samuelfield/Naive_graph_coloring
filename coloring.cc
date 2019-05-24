#include <iostream>
#include <thread>
#include <mutex>
#include <cilk/cilk.h>
#include "coloring.hh"
#include "schedule.hh"

// Boman coloring implementation
void boman_coloring(Graph& graph)
{
}

void naive_coloring(Graph& graph)
{
    Scheduler vertexSchedule(graph.sizeVertex());


    std::vector<int> neighbors;
    graph.getNeighbors(neighbors, 0);
}