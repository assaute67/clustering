#include "main.h"

double readStopThreshold(const std::string &filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cerr << "Error: Unable to open file " << filename << "\n";
        std::exit(1);
    }

    std::string line;
    for (int i = 1; i <= 14; ++i)
    {
        if (!std::getline(file, line))
        {
            std::cerr << "Error: File " << filename << " does not contain 14 lines.\n";
            std::exit(1);
        }
    }

    std::istringstream iss(line);
    double stopThreshold;
    if (!(iss >> stopThreshold))
    {
        std::cerr << "Error: Invalid stopThreshold value on line 14 of " << filename << ".\n";
        std::exit(1);
    }

    return stopThreshold;
}