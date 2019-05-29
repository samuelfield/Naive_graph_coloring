#include <iostream>
#include <thread>
#include <mutex>
#include <cilk/cilk.h>
#include "coloring.hh"
#include "bitsetscheduler.h"

// Boman coloring implementation
void boman_coloring(Graph& graph)
{
}


// Naive coloring implementation
void naive_coloring(Graph& graph)
{
    uint32_t numVertices = graph.sizeVertex();

    BitsetScheduler currentSchedule(numVertices);
    currentSchedule.reset();
    currentSchedule.scheduleAll(true);

    long iter = 0;
    while (iter < 5)
    {
        iter++;
        // std::cout << std::endl;
        if (currentSchedule.anyScheduledTasks() == false)
        {
            break;
        }
        // std::cout << "Iter: " << iter << std::endl; // Debug

        currentSchedule.newIteration();
        cilk_for(uint32_t v = 0; v < numVertices; v++)
        {
            if (currentSchedule.isScheduled(v))
            {
                // std::cout << "vertex: " << v << std::endl; // Debug
                std::vector<int> neighbors;
                uint32_t vDegree = graph.getNeighbors(neighbors, v);
                bool scheduleNeighbors = false;
                // int32_t oldVal = graph.getVertexValue(v); // Debug

                std::vector<bool> possibleValues(graph.getMaxDeg(), true);

                cilk_for(uint32_t n = 0; n < vDegree; n++)
                {
                    int32_t neighVal = graph.getVertexValue(neighbors[n]);
                    possibleValues[neighVal] = false;
                }

                // std::cout << std::endl; // Debug

                int32_t newValue = 0;
                while (newValue < (int32_t) graph.getMaxDeg())
                {
                    // std::cout << "Color: " << newValue << " is " << possibleValues[newValue] << std::endl; // Debug
                    if (possibleValues[newValue])
                    {
                        if (graph.getVertexValue(v) != newValue)
                        {
                            // std::cout << "Does not equal: " << graph.getVertexValue(v) << " != " << newValue << std::endl; // Debug
                            graph.setVertexValue(v, newValue);
                            scheduleNeighbors = true;
                        }
                        
                        break;
                    }

                    newValue++;
                }

                // std::cout << std::endl; // Debug

                if (scheduleNeighbors)
                {
                    // std::cout << "vertex: " << v << "    New Value: " << graph.getVertexValue(v) << "    Old Value: "  << oldVal << std::endl; // Debug
                    for (uint32_t n = 0; n < vDegree; n++)
                    {
                        currentSchedule.schedule(neighbors[n]);
                    }
                }
            }
        }
    }
}