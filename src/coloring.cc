#include <iostream>
#include <thread>
#include <mutex>

#include "coloring.hh"
#include "bitsetscheduler.h"
#include "parallel.h"

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
                int32_t vMaxValue = (int32_t) vDegree + 1;
                bool scheduleNeighbors = false;
                std::vector<bool> possibleValues(vMaxValue, true);

                cilk_for(uint32_t n = 0; n < vDegree; n++)
                {
                    int32_t neighVal = graph.getVertexValue(neighbors[n]);
                    possibleValues[neighVal] = false;
                }

                // std::cout << std::endl; // Debug

                // Find minimum color by iterating through color array in increasing order
                int32_t newValue = 0;
                while (newValue < vMaxValue)
                {
                    // std::cout << "Color: " << newValue << " is " << possibleValues[newValue] << std::endl; // Debug 
                    if (possibleValues[newValue])
                    {
                        if (graph.getVertexValue(v) != newValue)
                        {
                            // std::cout << "Does not equal: " << graph.getVertexValue(v) << " != " << newValue << std::endl; // Debug
                            graph.setVertexValue(v, newValue);
                        }
                        scheduleNeighbors = true;
                        
                        break;
                    }

                    newValue++;
                }

                if (scheduleNeighbors)
                {
                    for (uint32_t n = 0; n < vDegree; n++)
                    {
                        currentSchedule.schedule(neighbors[n]);
                    }
                }

                // std::cout << std::endl; // Debug
            }
        }
    }
}

bool assessGraph(Graph& graph)
{
    uint32_t numVertices = graph.sizeVertex();

    cilk_for(uint32_t v = 0; v < numVertices; v++)
    {
        int32_t vValue = graph.getVertexValue(v);
        std::vector<int> neighbors;
        uint32_t vDegree = graph.getNeighbors(neighbors, v);

        for(uint32_t n = 0; n < vDegree; n++)
        {
            int32_t neighVal = graph.getVertexValue(neighbors[n]);
            
            if (neighVal == vValue)
            {
                return false;
            }
        }
    }

    return true;
}