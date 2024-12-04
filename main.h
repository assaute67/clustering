#ifndef MAIN_H
#define MAIN_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <cmath>
#include <limits>
#include <opencv2/opencv.hpp>
#include <cstdlib>
#include <algorithm>
// #include <omp.h>
#include <random>
#include <ctime>

using namespace std;
using namespace cv;

struct MyPointSew
{
    int x, y;
    float brightness, time;
};

struct ClusterSew
{
    int x, y;
    float brightness, time;
    long long clusterId;
};

struct MyPoint
{
    double x, y, brightness, time;
};

struct MyPointWithCluster
{
    double x, y, brightness, time;
    int cluster = -1;
};

struct PointVid
{
    int x, y;
    float brightness, time; // Изменяем на float, так как brightness и time могут быть с плавающей точкой
    int cluster;
};

struct ClusterCenter
{
    double x, y, z, t;
    int clusterId; // Идентификатор кластера
};

struct KDNode
{
    ClusterCenter center;
    KDNode *left = nullptr;
    KDNode *right = nullptr;

    KDNode(const ClusterCenter &c) : center(c), left(nullptr), right(nullptr) {}
};

struct Cube
{
    int xIdx, yIdx, zIdx, tIdx;

    bool operator==(const Cube &other) const
    {
        return xIdx == other.xIdx && yIdx == other.yIdx && zIdx == other.zIdx && tIdx == other.tIdx;
    }
};

struct CubeHash
{
    std::size_t operator()(const Cube &c) const
    {
        return std::hash<int>()(c.xIdx) ^ (std::hash<int>()(c.yIdx) << 1) ^
               (std::hash<int>()(c.zIdx) << 2) ^ (std::hash<int>()(c.tIdx) << 3);
    }
};

KDNode *buildKDTree(std::vector<ClusterCenter>::iterator start,
                    std::vector<ClusterCenter>::iterator end, int depth);
bool kMeans(std::vector<MyPointWithCluster> &pointsWithCluster, std::vector<ClusterCenter> &centers, KDNode *kdTree, double stopThreshold);
void writeClustersToFile(const std::vector<MyPointWithCluster> &pointsWithCluster, const std::string &filename);
vector<MyPointWithCluster> readPointsWithCluster(const string &filename);
void nearestNeighborSearch(const KDNode *node, const MyPointWithCluster &p, int depth,
                           const KDNode *&bestNode, double &bestDist);
double squaredDistanceWithCluster(const MyPointWithCluster &p, const ClusterCenter &center);
vector<MyPoint> readPoints(const string &filename, double &brightnessMultiplier, double &timeMultiplier);
bool readMaxValues(const string &filename, double &frameWidth, double &frameHeight, double &frameCount, int &minClusterCount, double &brightnessMultiplier, double &timeMultiplier);
void writeGrid(const unordered_map<Cube, int, CubeHash> &cubeCounts,
               double cubeSizeX, double cubeSizeY, double cubeSizeZ, double cubeSizeT,
               const string &filename, int minClusterCount);
std::vector<ClusterCenter> readCenters(const std::string &filename);
double readStopThreshold(const std::string &filename);
void readPointsSew(const std::string &filename, std::vector<MyPointSew> &pointssew);
void readClustersSew(const std::string &filename, std::vector<ClusterSew> &clusterssew);
void writeOutputSew(const std::string &filename, const std::vector<MyPointSew> &pointssew, const std::vector<ClusterSew> &clusterssew);
std::vector<PointVid> readPointsFromFile(const std::string &filename);
cv::Scalar getRandomColor();
void generateVideo(const std::vector<PointVid> &points, const std::string &outputFilename);
// cv::VideoWriter videoWriter(outputFilename, cv::VideoWriter::fourcc('M', 'J', 'P', 'G'), frameRate, cv::Size(width, height));

#endif // MAIN_H
