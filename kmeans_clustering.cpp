#include "main.h"

bool kMeans(std::vector<MyPointWithCluster> &pointsWithCluster, std::vector<ClusterCenter> &centers, KDNode *kdTree, double stopThreshold)
{
    bool changed = false;
    double maxCenterShift = 0.0;

    // Step 1: Assign points to the nearest cluster centers
    // #pragma omp parallel for reduction(| : changed)
    for (size_t i = 0; i < pointsWithCluster.size(); ++i)
    {
        const KDNode *bestNode = nullptr;
        double bestDist = std::numeric_limits<double>::max();
        nearestNeighborSearch(kdTree, pointsWithCluster[i], 0, bestNode, bestDist);

        if (bestNode && pointsWithCluster[i].cluster != bestNode->center.clusterId)
        {
            changed = true;
            pointsWithCluster[i].cluster = bestNode->center.clusterId;
        }
    }

    // Step 2: Update cluster centers based on assigned points
    std::vector<ClusterCenter> newCenters(centers.size(), {0, 0, 0, 0, 0});
    std::vector<int> counts(centers.size(), 0);

    // #pragma omp parallel for
    for (size_t i = 0; i < pointsWithCluster.size(); ++i)
    {
        int clusterId = pointsWithCluster[i].cluster;
        if (clusterId != -1)
        {
            // #pragma omp atomic
            newCenters[clusterId].x += pointsWithCluster[i].x;
            // #pragma omp atomic
            newCenters[clusterId].y += pointsWithCluster[i].y;
            // #pragma omp atomic
            newCenters[clusterId].z += pointsWithCluster[i].brightness;
            // #pragma omp atomic
            newCenters[clusterId].t += pointsWithCluster[i].time;
            // #pragma omp atomic
            counts[clusterId]++;
        }
    }

    // #pragma omp parallel for reduction(max : maxCenterShift)
    for (int i = 0; i < centers.size(); ++i)
    {
        if (counts[i] > 0)
        {
            newCenters[i].x /= counts[i];
            newCenters[i].y /= counts[i];
            newCenters[i].z /= counts[i];
            newCenters[i].t /= counts[i];
            newCenters[i].clusterId = centers[i].clusterId;

            double shift = std::sqrt(std::pow(newCenters[i].x - centers[i].x, 2) +
                                     std::pow(newCenters[i].y - centers[i].y, 2) +
                                     std::pow(newCenters[i].z - centers[i].z, 2) +
                                     std::pow(newCenters[i].t - centers[i].t, 2));
            maxCenterShift = std::max(maxCenterShift, shift);
        }
        else
        {
            newCenters[i] = centers[i];
        }
    }

    centers = newCenters;
    return changed && maxCenterShift > stopThreshold;
}