#include "myAVLtree.hpp"

void treeMedian(const std::vector<int> *instructions)
{
    AVLTree small;
    AVLTree large;
    std::vector<int> medians;

    // main loop
    for (auto it = instructions->begin(); it != instructions->end(); ++it)
    {
        if (*it != -1) // add value either to small or large heap
        {
            // Check if empty and insert to correct position
            if (small.size() == 0 || *it <= small.find_max())
            {
                small.insert(*it);
            }
            else
            {
                large.insert(*it);
            }

            // Rebalance if necessary
            if (small.size() > large.size() + 1)
            {
                int largest = small.find_max();
                small.erase(largest);
                large.insert(largest);
            }
            else if (large.size() > small.size())
            {
                int smallest = large.find_min();
                large.erase(smallest);
                small.insert(smallest);
            }
        }
        else // pop median
        {
            // remove value and push onto medians
            int median = small.find_max();
            small.erase(median);
            medians.push_back(median);

            // // rebalance if neccessary
            if (small.size() < large.size())
            {
                int smallest = large.find_min();
                large.erase(smallest);
                small.insert(smallest);
            }
        }

    } // main loop end

    // Print output
    for (auto it = medians.begin(); it != medians.end(); ++it)
    {
        std::cout << *it << " ";
    }
}