#include "main.h"

std::vector<ClusterCenter> readCenters(const std::string &filename)
{
    std::vector<ClusterCenter> centers;
    std::ifstream file(filename);
    std::string line;
    int clusterId = 0;

    while (std::getline(file, line))
    {
        std::istringstream iss(line);
        ClusterCenter center;
        if (iss >> center.x >> center.y >> center.z >> center.t)
        {
            center.clusterId = clusterId++;
            centers.push_back(center);
        }
    }

    return centers;
}