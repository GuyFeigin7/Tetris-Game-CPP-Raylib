#pragma once

#include "grid.hpp"
#include "blocks.cpp"
#include "scoreManager.hpp"
#include "difficultyManager.hpp"

class Game
{
public:
    Game();

    // Initializes the game window and settings.
    void Init(int windowWidth, int windowHeight, int targetFPS, const char *fontPath, int fontSize);

    // Starts the main game loop.
    void Run();
    
private:
    // Renders the game elements on the screen.
    void Draw();

    // Handles user input for controlling the game.
    void HandleInput();

    void MoveBlockDown();
    bool IsBlockOutside();
    void RotateBlock();
    void LockBlock();
    bool BlockFits();

     // Resets the game state for a new game.
    void Reset();
    
    std::vector<Block> GetAllBlocks();
    Block GetRandomBlock();
    void MoveBlockLeft();
    void MoveBlockRight();

    // Checks if a specified time interval has passed since the last event update.
    bool EventTriggered(double interval);

    void DisplayPauseMenu();

    Grid grid;
    std::vector<Block> blocks;
    Block currentBlock;
    Block nextBlock;
    ScoreManager scoreManager;
    DifficultyManager difficultyManager;
    
    bool gameOver;
    bool gamePaused;
    bool exitGame;
    double lastUpdateTime;
    Font font;
    float movementDelay; // Delay between moves in seconds
    float lastMoveTime; // Time of the last move
};