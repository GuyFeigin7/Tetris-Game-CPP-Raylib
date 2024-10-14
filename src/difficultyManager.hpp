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
    double difficulty; // Current difficulty level. Lower = harder.
    double difficultyFactor; // Scoring is increased by this factor based on difficulty level
    int nextDifficulty; 
    int maxDifficulty;
    int difficultyNum; //Numerical representation of the difficulty to be shown on screen.
};