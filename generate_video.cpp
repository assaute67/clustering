#include "main.h"

// Функция для генерации случайного цвета для каждого кластера
cv::Scalar getRandomColor()
{
    // Генерация случайных значений для красного, зеленого и синего канала
    int r = rand() % 256;
    int g = rand() % 256;
    int b = rand() % 256;
    return cv::Scalar(b, g, r); // OpenCV использует формат BGR
}

// Функция для создания видео из точек
void generateVideo(const std::vector<PointVid> &points, const std::string &outputFilename)
{
    int width = 400;
    int height = 272;
    int frameRate = 30;

    cv::VideoWriter videoWriter(outputFilename, cv::VideoWriter::fourcc('M', 'J', 'P', 'G'), frameRate, cv::Size(width, height));

    int maxTime = 0;
    for (const auto &p : points)
    {
        maxTime = std::max(maxTime, static_cast<int>(p.time));
    }

    // Создаем карту для хранения цветов кластеров
    std::unordered_map<int, cv::Scalar> clusterColors;
    srand(static_cast<unsigned int>(time(0))); // Инициализация генератора случайных чисел

    // Создание кадров для каждого времени
    for (int t = 0; t <= maxTime; ++t)
    {
        cv::Mat frame(height, width, CV_8UC3, cv::Scalar(0, 0, 0)); // черный фон

        // Рисуем точки на кадре
        for (const auto &p : points)
        {
            if (static_cast<int>(p.time) == t)
            {
                // Если для этого кластера еще не выбран цвет, генерируем новый
                if (clusterColors.find(p.cluster) == clusterColors.end())
                {
                    clusterColors[p.cluster] = getRandomColor();
                }

                // Рисуем точку с соответствующим цветом
                cv::Scalar color = clusterColors[p.cluster];
                cv::circle(frame, cv::Point(p.x, p.y), 2, color, -1); // рисуем точку
            }
        }

        videoWriter.write(frame);
    }
}