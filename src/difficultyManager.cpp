#include "difficultyManager.hpp"

DifficultyManager::DifficultyManager() : difficulty(0.3),
                                         difficultyFactor(1),
                                         nextDifficulty(1000),
                                         maxDifficulty(64000),
                                         difficultyNum(1)
{
}

void DifficultyManager::UpdateDifficulty(int currentScore, const Sound& levelUpSound)
{
    if (currentScore >= nextDifficulty && currentScore <= maxDifficulty)
    {
        difficulty = difficulty * 0.9;
        nextDifficulty *= 2;
        difficultyFactor += 0.5;
        ++difficultyNum;
        PlaySound(levelUpSound);
    }
}

double DifficultyManager::GetDifficultyFactor()
{
    return difficultyFactor;
}

double DifficultyManager::GetDifficulty()
{
    return difficulty;
}

int DifficultyManager::GetDifficultyNum()
{
    return difficultyNum;
}

void DifficultyManager::ResetDifficulty()
{
    difficulty = 0.3;
    difficultyFactor = 1;
    nextDifficulty = 1000;
    difficultyNum = 1;
}
