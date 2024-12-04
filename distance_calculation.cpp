#include "main.h"

double squaredDistance(const Point &p, const ClusterCenter &center)
{
    return std::pow(p.x - center.x, 2) + std::pow(p.y - center.y, 2) +
           std::pow(p.brightness - center.z, 2) + std::pow(p.time - center.t, 2);
}