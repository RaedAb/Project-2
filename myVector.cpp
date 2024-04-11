#include <iostream>
#include <chrono>
#include "myVector.hpp"

void vectorMedian(const std::vector<int> *instructions)
{
    std::vector<int> vec;
    std::vector<int> medians;

    // main loop
    for (auto it = instructions->begin(); it != instructions->end(); ++it)
    {
        if (*it != -1) // add while sort
        {
            auto pos = std::lower_bound(vec.begin(), vec.end(), *it);
            vec.insert(pos, *it);
        }
        else // pop median
        {
            int med = vec.size() / 2;
            if (vec.size() % 2 == 1)
            {
                // Odd number of elements, return the middle element
                medians.push_back(vec[med]);
                vec.erase(vec.begin() + med);
            }
            else
            {
                // Even number of elements, return the lower of the two middle elements
                medians.push_back(vec[med - 1]);
                vec.erase(vec.begin() + (med - 1));
            }
        }
    } // main loop end

    // Print output
    for (auto it = medians.begin(); it != medians.end(); ++it)
    {
        std::cout << *it << " ";
    }
}