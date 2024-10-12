#include <fstream>
#include <iostream>

#include "scoreManager.hpp"

ScoreManager::ScoreManager() : score(0)
{
}

void ScoreManager::UpdateScore(int linesCleared, int moveDownPoints, double difficultyFactor)
{
    switch (linesCleared)
    {
        case 1:
        {
            score += 100 * difficultyFactor;
            break;
        }
        case 2:
        {
            score += 300 * difficultyFactor;
            break;
        }
        case 3:
        {
            score += 600 * difficultyFactor;
            break;
        }
        case 4:
        {
            score += 1000 * difficultyFactor;
            break;
        }
    }

    score += moveDownPoints;

    if (score > GetHighestScore())
    {
        SaveHighestScore();
    }
}

void ScoreManager::SaveHighestScore()
{
    std::ofstream file("Data/scores.txt");
    if (file.is_open())
    {
        file << score;
        file.close();
    }
    else
    {
        std::cerr << "Unable to open file for writing.\n";
    }
}

int ScoreManager::GetHighestScore() 
{
    std::ifstream file("Data/scores.txt");
    int highestScore = 0;

    if (file.is_open())
    {
        file >> highestScore;
        file.close();
    }
    else
    {
        std::cerr << "Unable to open file for reading.\n";
    }

    return highestScore;
}

int ScoreManager::GetScore() 
{
    return score;
}

void ScoreManager::ResetScore()
{
    score = 0;
}
