#include <iostream>
#include <chrono>
#include "myList.hpp"

void listMedian(const std::vector<int> *instructions)
{
    std::list<int> lst;
    std::vector<int> medians;

    // main loop
    for (auto it = instructions->begin(); it != instructions->end(); ++it)
    {
        if (*it != -1) // add while sort
        {
            auto pos = lst.begin();
            while (pos != lst.end() && *pos < *it)
            {
                pos++;
            }

            lst.insert(pos, *it);
        }
        else // pop median
        {
            int med = lst.size() / 2;
            if (lst.size() % 2 == 1)
            {
                auto it = lst.begin();
                std::advance(it, med);
                medians.push_back(*it);
                lst.erase(it);
            }
            else
            {
                auto it = lst.begin();
                std::advance(it, med - 1);
                medians.push_back(*it);
                lst.erase(it);
            }
        }
    } // main loop end

    // Print output
    for (auto it = medians.begin(); it != medians.end(); ++it)
    {
        std::cout << *it << " ";
    }
}