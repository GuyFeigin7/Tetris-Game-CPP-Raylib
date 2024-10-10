#pragma once

#include "grid.hpp"
#include "blocks.cpp"

class Game
{
public:
    Game();
    ~Game();
    void Init(int windowWidth, int windowHeight, int targetFPS, const char *fontPath, int fontSize);
    void Run();
    
private:
    void Draw();
    void HandleInput();
    void MoveBlockDown();
    int GetHighestScore();
    bool IsBlockOutside();
    void RotateBlock();
    void LockBlock();
    bool BlockFits();
    void Reset();
    void UpdateScore(int linesCleared, int moveDownPoints);
    std::vector<Block> GetAllBlocks();
    Block GetRandomBlock();
    void MoveBlockLeft();
    void MoveBlockRight();
    void SaveHighestScore();
    bool EventTriggered(double interval);
    void UpdateDifficulty();

    Grid grid;
    std::vector<Block> blocks;
    Block currentBlock;
    Block nextBlock;
    Sound rotateSound;
    Sound clearSound;
    Sound gameOverSound;
    Sound levelUp;
    
    int score;
    bool gameOver;
    Music music;
    double lastUpdateTime;
    Font font;
    double difficulty;
    double difficultyFactor;
    int nextDifficulty;
    int maxDifficulty;
    int difficultyNum;
};