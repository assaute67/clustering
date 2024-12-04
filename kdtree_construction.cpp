#include "main.h"

KDNode *buildKDTree(std::vector<ClusterCenter>::iterator start,
                    std::vector<ClusterCenter>::iterator end, int depth)
{
    if (start >= end)
        return nullptr;

    int axis = depth % 4; // Cycle through dimensions: x, y, z, t
    auto mid = start + (end - start) / 2;

    std::nth_element(start, mid, end, [axis](const ClusterCenter &a, const ClusterCenter &b)
                     {
        switch (axis)
        {
        case 0:
            return a.x < b.x;
        case 1:
            return a.y < b.y;
        case 2:
            return a.z < b.z;
        default:
            return a.t < b.t;
        } });

    KDNode *node = new KDNode(*mid);
    node->left = buildKDTree(start, mid, depth + 1);
    node->right = buildKDTree(mid + 1, end, depth + 1);

    return node;
}