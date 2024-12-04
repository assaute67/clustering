#include "main.h"

void writeClustersToFile(const std::vector<MyPointWithCluster> &pointsWithCluster, const std::string &filename)
{
    std::ofstream file(filename);

    for (const auto &p : pointsWithCluster)
    {
        file << p.x << " " << p.y << " " << p.brightness << " " << p.time << " " << p.cluster << "\n";
    }
}