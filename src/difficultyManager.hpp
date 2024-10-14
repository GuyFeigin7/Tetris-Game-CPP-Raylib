#pragma once

#include <raylib.h>

class DifficultyManager
{
public:
    DifficultyManager();
    void UpdateDifficulty(int currentScore);
    double GetDifficultyFactor();
    double GetDifficulty();
    int GetDifficultyNum();
    void ResetDifficulty();

private:
    double difficulty;
    double difficultyFactor;
    int nextDifficulty;
    int maxDifficulty;
    int difficultyNum;
};