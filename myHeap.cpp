#include <iostream>
#include "myHeap.hpp"

void heapMedian(const std::vector<int> *instructions)
{
    std::priority_queue<int> small;
    // Min heap for large container so that top element is smallest
    std::priority_queue<int, std::vector<int>, std::greater<int>> large;
    std::vector<int> medians;

    // main loop
    for (auto it = instructions->begin(); it != instructions->end(); ++it)
    {
        if (*it != -1) // add value either to small or large heap
        {
            // Check if empty and insert to correct position
            if (small.empty() || *it <= small.top())
            {
                small.push(*it);
            }
            else
            {
                large.push(*it);
            }

            // Rebalance if necessary
            if (small.size() > large.size() + 1)
            {
                large.push(small.top());
                small.pop();
            }
            else if (large.size() > small.size())
            {
                small.push(large.top());
                large.pop();
            }
        }
        else // pop median
        {
            medians.push_back(small.top());
            small.pop();

            // rebalance if neccessary
            if (small.size() < large.size())
            {
                small.push(large.top());
                large.pop();
            }
        }
    } // main loop end

    // Print output
    for (auto it = medians.begin(); it != medians.end(); ++it)
    {
        std::cout << *it << " ";
    }
}