#pragma once

#include "difficultyManager.hpp"

class ScoreManager
{
public:
    ScoreManager();
    void UpdateScore(int linesCleared, int moveDownPoints, double difficultyFactor);
    void SaveHighestScore(); 
    int GetHighestScore(); 
    int GetScore(); 
    void ResetScore();

private:
    int score;
};