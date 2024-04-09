#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

// Read from txt file and preform insert or pop operations and store in vector
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

int main()
{
    std::ifstream file("testinput.txt"); // Open input file

    if (!file.is_open())
    {
        std::cerr << "Unable to open file.\n";
        return 1;
    }

    std::string line;
    std::vector<int> instructions;
    while (std::getline(file, line))
    {
        // store line in iss to parse
        std::istringstream iss(line);
        std::string operation, x;

        // Extract operation and x from the line
        if (!(iss >> operation >> x))
        {
            std::cerr << "Error reading line.\n";
            continue;
        }

        // Store into integer
        if (operation == "insert")
        {
            instructions.push_back(std::stoi(x));
        }
        else
        {
            instructions.push_back(-1);
        }
    }

    file.close(); // Close the file

    for (auto it = instructions.begin(); it != instructions.end(); ++it)
    {
        std::cout << *it << " ";
    }

    return 0;
}
