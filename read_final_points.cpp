#include "main.h"

std::vector<PointVid> readPointsFromFile(const std::string &filename)
{
    std::vector<PointVid> points;
    std::ifstream file(filename);
    std::string line;

    while (std::getline(file, line))
    {
        std::istringstream iss(line);
        PointVid p;
        iss >> p.x >> p.y >> p.brightness >> p.time >> p.cluster;
        points.push_back(p);
    }
    return points;
}