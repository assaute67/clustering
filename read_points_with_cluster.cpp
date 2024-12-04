#include "main.h"

vector<MyPointWithCluster> readPointsWithCluster(const string &filename)
{
    vector<MyPointWithCluster> points;
    ifstream file(filename);
    string line;

    while (getline(file, line))
    {
        istringstream iss(line);
        MyPointWithCluster p;
        if (iss >> p.x >> p.y >> p.brightness >> p.time)
        {
            points.push_back(p);
        }
    }

    return points;
}