#include "main.h"

vector<MyPoint> readPoints(const string &filename, double &brightnessMultiplier, double &timeMultiplier)
{
    vector<MyPoint> points;
    ifstream file(filename);
    string line;

    while (getline(file, line))
    {
        istringstream iss(line);
        MyPoint p;
        double brightnessValue, timeValue;
        if (iss >> p.x >> p.y >> brightnessValue >> timeValue)
        {
            p.brightness = brightnessValue * brightnessMultiplier;
            p.time = timeValue * timeMultiplier;
        }

        {
            points.push_back(p);
        }
    }

    return points;
}