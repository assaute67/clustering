#include "main.h"

bool readMaxValues(const string &filename, double &frameWidth, double &frameHeight, double &frameCount, int &minClusterCount, double &brightnessMultiplier, double &timeMultiplier)
{
    ifstream file(filename);
    string line;

    for (int lineNumber = 1; getline(file, line); ++lineNumber)
    {
        istringstream iss(line);
        if (lineNumber == 2)
        {
            iss >> frameWidth;
        }
        else if (lineNumber == 4)
        {
            iss >> frameHeight;
        }
        else if (lineNumber == 6)
        {
            iss >> frameCount;
        }
        else if (lineNumber == 8)
        {
            iss >> minClusterCount;
        }
        else if (lineNumber == 16)
        {
            iss >> brightnessMultiplier;
            cout << "Brightness Multiplier: " << brightnessMultiplier << endl; // Выводим значение для диагностики
        }
        else if (lineNumber == 18)
        {
            iss >> timeMultiplier;
            cout << "Time Multiplier: " << timeMultiplier << endl; // Выводим значение для диагностики
        }
    }

    return (frameWidth > 0 && frameHeight > 0 && frameCount > 0 && minClusterCount > 0 && brightnessMultiplier > 0 && timeMultiplier > 0);
}
