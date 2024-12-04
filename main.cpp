#include "main.h"

int main()
{
    string pointsFile = "points.txt";
    string maxValuesFile = "input.txt";
    string outputGridFile = "grid.txt";
    std::string outputClustersFile = "clusters.txt";
    std::ofstream outputFile("finalclusters.txt");

    double frameWidth = 0.0, frameHeight = 0.0, frameCount = 0.0;
    int minClusterCount = 0;
    double brightnessMultiplier = 0.0, timeMultiplier = 0.0;

    // Получаем максимальные значения характеристик
    if (!readMaxValues(maxValuesFile, frameWidth, frameHeight, frameCount, minClusterCount, brightnessMultiplier, timeMultiplier))
    {
        cerr << "Ошибка при чтении значений из файла " << maxValuesFile << endl;
        return -1;
    }

    // Читаем точки из points.txt
    vector<MyPoint> points = readPoints(pointsFile, brightnessMultiplier, timeMultiplier);
    if (points.empty())
    {
        cerr << "Ошибка при чтении точек из файла " << pointsFile << endl;
        return -1;
    }

    // Определяем размер ячейки
    unordered_map<Cube, int, CubeHash> cubeCounts;
    double cubeSizeX = frameWidth * 0.1;
    double cubeSizeY = frameHeight * 0.1;
    double cubeSizeZ = 255 * 0.1; // Максимальная яркость
    double cubeSizeT = frameCount * 0.1;

    // Считаем, сколько точек в каждой ячейке
    for (const auto &p : points)
    {
        int xIdx = static_cast<int>(p.x / cubeSizeX);
        int yIdx = static_cast<int>(p.y / cubeSizeY);
        int zIdx = static_cast<int>(p.brightness / cubeSizeZ);
        int tIdx = static_cast<int>(p.time / cubeSizeT);

        Cube cube = {xIdx, yIdx, zIdx, tIdx};
        cubeCounts[cube]++;
    }

    writeGrid(cubeCounts, cubeSizeX, cubeSizeY, cubeSizeZ, cubeSizeT, outputGridFile, minClusterCount);

    cout << "Готово! Результаты сохранены в файл " << outputGridFile << endl;

    auto pointsWithCluster = readPointsWithCluster(pointsFile);
    auto centers = readCenters(outputGridFile);
    double stopThreshold = readStopThreshold(maxValuesFile);

    if (pointsWithCluster.empty() || centers.empty())
    {
        std::cerr << "Error: Missing points or cluster centers data.\n";
        return 1;
    }

    KDNode *kdTree = buildKDTree(centers.begin(), centers.end(), 0);

    // Run k-means clustering
    bool changed;
    int iterations = 0, maxIterations = 100;
    do
    {
        changed = kMeans(pointsWithCluster, centers, kdTree, stopThreshold);
    } while (changed && ++iterations < maxIterations);

    // Print clustering status
    std::cout << "Кластеризация завершена после " << iterations << " итераций.\n";
    std::cout << "Количество кластеров: " << centers.size() << "\n";
    std::cout << "Результат сохранен в " << outputClustersFile << ".\n";

    writeClustersToFile(pointsWithCluster, outputClustersFile);

    std::vector<MyPointSew> pointssew;
    std::vector<ClusterSew> clusterssew;

    // Чтение точек и кластеров из файлов
    readPointsSew("points.txt", pointssew);
    readClustersSew("clusters.txt", clusterssew);

    // Проверка на соответствие количества точек и кластеров
    if (pointssew.size() != clusterssew.size())
    {
        std::cerr << "Количество точек и кластеров не совпадает!" << std::endl;
        return 1;
    }

    // Запись в файл finalclusters.txt
    writeOutputSew("finalclusters.txt", pointssew, clusterssew);

    std::string outputVid = "output_video.avi";

    std::vector<PointVid> finalpoints = readPointsFromFile(outputClustersFile);
    generateVideo(finalpoints, outputVid);

    std::cout << "Video generated successfully!" << std::endl;

    return 0;
}