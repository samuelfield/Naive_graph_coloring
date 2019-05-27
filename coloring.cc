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
    int j = 0;
    while (j < 5)
    {
        // std::cout << std::endl;
        if (vertexSchedule.completed())
        {
            break;
        }
        // std::cout << "Iter: " << j << std::endl; // Debug
        for(uint32_t v = 0; v < graph.sizeVertex(); v++)
        {
            if (vertexSchedule.checkItem(v))
            {
                // std::cout << "vertex: " << v << std::endl; // Debug
                vertexSchedule.setItem(v, false);
                std::vector<int> neighbors;
                uint32_t vDegree = graph.getNeighbors(neighbors, v);
                bool scheduleNeighbors = false;
                // int32_t oldVal = graph.getVertexValue(v); // Debug

                std::vector<bool> possibleValues(graph.getMaxDeg(), true);

                for (uint32_t n = 0; n < vDegree; n++)
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
                        vertexSchedule.setItem(neighbors[n], true);
                    }
                }
            }
        }

        j++;
    }
    

}