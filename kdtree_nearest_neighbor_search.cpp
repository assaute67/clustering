#include "main.h"

void nearestNeighborSearch(const KDNode *node, const MyPointWithCluster &p, int depth,
                           const KDNode *&bestNode, double &bestDist)
{
    if (!node)
        return;

    double dist = squaredDistanceWithCluster(p, node->center);
    if (dist < bestDist)
    {
        bestDist = dist;
        bestNode = node;
    }

    int axis = depth % 4;
    double diff;
    switch (axis)
    {
    case 0:
        diff = p.x - node->center.x;
        break;
    case 1:
        diff = p.y - node->center.y;
        break;
    case 2:
        diff = p.brightness - node->center.z;
        break;
    default:
        diff = p.time - node->center.t;
        break;
    }

    nearestNeighborSearch(diff < 0 ? node->left : node->right, p, depth + 1, bestNode, bestDist);
    if (std::abs(diff) < bestDist)
        nearestNeighborSearch(diff < 0 ? node->right : node->left, p, depth + 1, bestNode, bestDist);
}