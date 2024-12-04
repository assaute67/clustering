#include "main.h"

void readPointsSew(const std::string &filename, std::vector<MyPointSew> &pointssew)
{
    std::ifstream pointsFile(filename);
    if (!pointsFile.is_open())
    {
        std::cerr << "Ошибка при открытии файла: " << filename << std::endl;
        return;
    }

    std::string line;
    while (std::getline(pointsFile, line))
    {
        std::stringstream ss(line);
        MyPointSew p;
        if (ss >> p.x >> p.y >> p.brightness >> p.time)
        {
            pointssew.push_back(p);
        }
        else
        {
            std::cerr << "Ошибка при считывании строки: " << line << std::endl;
        }
    }
}

void readClustersSew(const std::string &filename, std::vector<ClusterSew> &clusterssew)
{
    std::ifstream clustersFile(filename);
    if (!clustersFile.is_open())
    {
        std::cerr << "Ошибка при открытии файла: " << filename << std::endl;
        return;
    }

    std::string line;
    while (std::getline(clustersFile, line))
    {
        std::stringstream ss(line);
        ClusterSew c;
        if (ss >> c.x >> c.y >> c.brightness >> c.time >> c.clusterId)
        {
            clusterssew.push_back(c);
        }
        else
        {
            std::cerr << "Ошибка при считывании строки из " << filename << ": " << line << std::endl;
        }
    }
}

void writeOutputSew(const std::string &filename, const std::vector<MyPointSew> &pointssew, const std::vector<ClusterSew> &clusterssew)
{
    std::ofstream outputFile(filename);
    if (!outputFile.is_open())
    {
        std::cerr << "Ошибка при открытии файла для записи: " << filename << std::endl;
        return;
    }

    for (size_t i = 0; i < pointssew.size(); ++i)
    {
        const MyPointSew &p = pointssew[i];
        const ClusterSew &c = clusterssew[i];
        outputFile << p.x << " " << p.y << " " << p.brightness << " " << p.time << " " << c.clusterId << std::endl;
    }

    std::cout << "Файл " << filename << " успешно создан!" << std::endl;
}
