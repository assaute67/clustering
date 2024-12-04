#include "main.h"

void writeGrid(const unordered_map<Cube, int, CubeHash> &cubeCounts,
               double cubeSizeX, double cubeSizeY, double cubeSizeZ, double cubeSizeT,
               const string &filename, int minClusterCount)
{
    ofstream file(filename);
    int validClusterCount = 0; // Переменная для подсчета валидных кластеров

    for (const auto &entry : cubeCounts)
    {
        int count = entry.second;
        if (count >= minClusterCount)
        {
            Cube cube = entry.first;
            double centerX = (cube.xIdx + 0.5) * cubeSizeX;
            double centerY = (cube.yIdx + 0.5) * cubeSizeY;
            double centerZ = (cube.zIdx + 0.5) * cubeSizeZ;
            double centerT = (cube.tIdx + 0.5) * cubeSizeT;
            file << centerX << " " << centerY << " " << centerZ << " " << centerT << "\n";
            validClusterCount++; // Увеличиваем счетчик валидных кластеров
        }
    }

    cout << "Количество конечных кластеров: " << validClusterCount << endl; // Выводим количество кластеров в консоль
}
