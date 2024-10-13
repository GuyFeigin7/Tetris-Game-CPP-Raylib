#pragma once

#include "grid.hpp"
#include "blocks.cpp"
#include "scoreManager.hpp"
#include "difficultyManager.hpp"
#include "soundManager.hpp"

class Game
{
public:
    Game();
    void Init(int windowWidth, int windowHeight, int targetFPS, const char *fontPath, int fontSize);
    void Run();
    
private:
    void Draw();
    void HandleInput();
    void MoveBlockDown();
    bool IsBlockOutside();
    void RotateBlock();
    void LockBlock();
    bool BlockFits();
    void Reset();
    std::vector<Block> GetAllBlocks();
    Block GetRandomBlock();
    void MoveBlockLeft();
    void MoveBlockRight();
    bool EventTriggered(double interval);
    void DisplayPauseMenu();

    Grid grid;
    std::vector<Block> blocks;
    Block currentBlock;
    Block nextBlock;
    ScoreManager scoreManager;
    DifficultyManager difficultyManager;
    SoundManager soundManager;
    
    bool gameOver;
    bool gamePaused;
    bool exitGame;
    double lastUpdateTime;
    Font font;
    float movementDelay;  // Delay between moves in seconds
    float lastMoveTime;       // Time of the last move
};