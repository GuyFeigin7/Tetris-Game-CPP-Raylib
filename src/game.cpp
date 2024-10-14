#include <iostream>

#include "raylib.h"
#include "game.hpp"
#include "soundManager.hpp"

Game::Game() : blocks(GetAllBlocks()),
               gameOver(false),
               lastUpdateTime(0),
               movementDelay(0.1f),
               lastMoveTime(0),
               gamePaused(false),
               exitGame(false)
{
    srand(static_cast<unsigned int>(time(0)));
    currentBlock = GetRandomBlock(); 
    nextBlock = GetRandomBlock();
}

void Game::Init(int windowWidth, int windowHeight, int targetFPS, const char *fontPath, int fontSize)
{
    InitWindow(windowWidth, windowHeight, "Raylib Tetris");
	SetTargetFPS(targetFPS);
	font = LoadFontEx(fontPath, fontSize, 0, 0);
}

void Game::Run()
{
    while (!WindowShouldClose())
	{
		HandleInput();
		
        if (exitGame)
        {
            break;
        }
        else if (gamePaused)
        {
            DisplayPauseMenu();
        }
        else
        {
            SoundManager::GetInstance().PlayMusic();

            if (EventTriggered(difficultyManager.GetDifficulty()))
            {
                MoveBlockDown();
            }

            BeginDrawing();
            ClearBackground(darkBlue);
            DrawTextEx(font, "Score", {365, 15}, 38, 2, WHITE);
            DrawTextEx(font, "Difficulty", {330, 125}, 28, 2, GREEN);
            DrawRectangleRounded({320, 160,  170, 60}, 0.3, 6, lightBlue);

            char difficultyText[10];
            sprintf(difficultyText, "%d", difficultyManager.GetDifficultyNum());
            Vector2 difficultyTextSize = MeasureTextEx(font, difficultyText, 38, 2);
            DrawTextEx(font, difficultyText, {320 + (170 - difficultyTextSize.x) / 2, 170}, 30, 2, WHITE);

            DrawTextEx(font, "Next", {370, 240}, 38, 2, WHITE);
            if (gameOver)
            {
                DrawTextEx(font, "GAME OVER", {330, 520}, 29, 2, RED);
                DrawTextEx(font, "Press 'R' to\nrestart", {330, 565}, 20, 2, WHITE);
            }
            DrawRectangleRounded({320, 55,  170, 60}, 0.3, 6, lightBlue);

            char scoreText[10];
            sprintf(scoreText, "%d", scoreManager.GetScore());
            Vector2 textSize = MeasureTextEx(font, scoreText, 38, 2);
            DrawTextEx(font, scoreText, {320 + (170 - textSize.x) / 2, 65}, 38, 2, WHITE);

            int highestScore = scoreManager.GetHighestScore();
            char highScoreText[10];
            sprintf(highScoreText, "%d", highestScore);
            Vector2 scoreTextSize = MeasureTextEx(font, highScoreText, 38, 2);
            DrawTextEx(font, "High Score", {320, 425}, 30, 2, YELLOW);
            DrawTextEx(font, highScoreText, {320 + (185 - scoreTextSize.x) / 2, 465}, 30, 2, WHITE);
            
            DrawRectangleRounded({320, 280,  170, 140}, 0.3, 6, lightBlue); //Next block rectangle
            Draw();

            EndDrawing();
        }
	}

    Reset();
    ClearBackground(darkBlue);
}

Block Game::GetRandomBlock()
{
    if (blocks.empty())
    {
        blocks = GetAllBlocks();
    }

    int randomIndex = rand() % blocks.size();
    Block block = blocks[randomIndex];
    blocks.erase(blocks.begin() + randomIndex);
    return block;
}

std::vector<Block> Game::GetAllBlocks()
{
    return {IBlock(), JBlock(), LBlock(), OBlock(), SBlock(), TBlock(), ZBlock()};
}

void Game::Draw()
{
    grid.Draw();
    currentBlock.Draw(11, 11);
    switch (nextBlock.id)
    {
        case 3:
        {
            nextBlock.Draw(255, 340);
            break;
        }
        case 4:
        {
            nextBlock.Draw(255, 330);
            break;
        }
        default:
        {
            nextBlock.Draw(270, 320);
            break;
        }
    }
}

void Game::HandleInput()
{
    float currentTime = GetTime();  // Get current time in seconds

    if (gameOver && IsKeyPressed(KEY_R))  // Reset game only on initial key press
    {
        gameOver = false;
        Reset();
    }
    if (IsKeyPressed(KEY_P)) // Pause game and display pause menu
    {
        gamePaused = true; 
    }
    if (IsKeyDown(KEY_LEFT) && currentTime - lastMoveTime >= movementDelay)  // Move left
    {
        MoveBlockLeft();
        lastMoveTime = currentTime;  // Update the last move time
    }
    if (IsKeyDown(KEY_RIGHT) && currentTime - lastMoveTime >= movementDelay)  // Move right
    {
        MoveBlockRight();
        lastMoveTime = currentTime;  // Update the last move time
    }
    if (IsKeyDown(KEY_DOWN) && currentTime - lastMoveTime >= movementDelay)  // Move down
    {
        MoveBlockDown();
        if (!gameOver)
        {
            scoreManager.UpdateScore(0, 5, difficultyManager.GetDifficultyFactor());
            difficultyManager.UpdateDifficulty(scoreManager.GetScore());
        }
        lastMoveTime = currentTime;  // Update the last move time
    }
    if (IsKeyPressed(KEY_SPACE))  // Only rotate block on initial SPACE press
    {
        RotateBlock();
    }
}

void Game::MoveBlockLeft()
{
    if (!gameOver)
    {
        currentBlock.Move(0, -1);
        if (IsBlockOutside() || !BlockFits())
        {
            currentBlock.Move(0, 1);
        }
    }
}

void Game::MoveBlockRight()
{
    if (!gameOver)
    {
        currentBlock.Move(0, 1);
        if (IsBlockOutside() || !BlockFits())
        {
            currentBlock.Move(0, -1);
        }
    }
}

bool Game::EventTriggered(double interval)
{
    double currentTime = GetTime();
	if (currentTime - lastUpdateTime >= interval)
	{
		lastUpdateTime = currentTime;
		return true;
	}
	return false;
}

void Game::DisplayPauseMenu()
{
    int selectedOption = 0;
    std::vector<std::string> options = { "Resume", "Restart Game", "Exit to Main Menu" };
    
    while (gamePaused)
    {
        BeginDrawing();
        ClearBackground(BLACK);

        // Draw the pause menu options
        for (int i = 0; i < options.size(); ++i)
        {
            Color color = (i == selectedOption) ? GREEN : WHITE;
            DrawText(options[i].c_str(), 50, 200 + i * 50, 40, color);
        }

        // Handle input to navigate the pause menu
        if (IsKeyPressed(KEY_DOWN))
        {
            SoundManager::GetInstance().PlaySelectedOptionSound();
            selectedOption = (selectedOption + 1) % options.size();
        }
        else if (IsKeyPressed(KEY_UP))
        {
            SoundManager::GetInstance().PlaySelectedOptionSound();
            selectedOption = (selectedOption - 1 + options.size()) % options.size();
        }
        else if (IsKeyPressed(KEY_ENTER))
        {
            SoundManager::GetInstance().PlayEnterSound();
            if (selectedOption == 0)  // Resume game
            {
                gamePaused = false;
            }
            else if (selectedOption == 1) // Restart Game
            {
                Reset();
            }
            else if (selectedOption == 2)  // Exit to Main Menu
            {
                gamePaused = false;
                exitGame = true;
            }
        }

        EndDrawing();
    }
}

void Game::MoveBlockDown()
{
    if (!gameOver)
    {
        currentBlock.Move(1, 0);
        if (IsBlockOutside() || !BlockFits())
        {
            currentBlock.Move(-1, 0);
            LockBlock();
        }
    }
}

bool Game::IsBlockOutside()
{
    std::vector<Position> tiles = currentBlock.GetCellPositions();
    for (Position item : tiles)
    {
        if (grid.IsCellOutside(item.row, item.col))
        {
            return true;
        }
    }

    return false;
}

void Game::RotateBlock()
{
    if (!gameOver)
    {
        currentBlock.Rotate();
        if (IsBlockOutside() || !BlockFits())
        {
            currentBlock.UndoRotation();
        }
        else
        {
            SoundManager::GetInstance().PlayRotateSound();
        }
    }
}

void Game::LockBlock()
{
    std::vector<Position> tiles = currentBlock.GetCellPositions();
    for (Position item : tiles)
    {
        grid.grid[item.row][item.col] = currentBlock.id;
    }

    currentBlock = nextBlock;
    if (!BlockFits())
    {
        gameOver = true;
        SoundManager::GetInstance().PlayGameOverSound();
    }

    nextBlock = GetRandomBlock();
    int rowsCleared = grid.ClearFullRows();
    if (rowsCleared > 0)
    {
        SoundManager::GetInstance().PlayClearSound();
        scoreManager.UpdateScore(rowsCleared, 0, difficultyManager.GetDifficultyFactor());
    }
}

bool Game::BlockFits()
{
    std::vector<Position> tiles = currentBlock.GetCellPositions();
    for (Position item : tiles)
    {
        if (!grid.IsCellEmpty(item.row, item.col))
        {
            return false;
        }
    }
    return true;
}

void Game::Reset()
{
    grid.Initialize();
    blocks = GetAllBlocks();
    currentBlock = GetRandomBlock();
    nextBlock = GetRandomBlock();
    scoreManager.ResetScore();
    difficultyManager.ResetDifficulty();
    SoundManager::GetInstance().StopMusic();
    SoundManager::GetInstance().ResetMusic();
    gameOver = false;
    gamePaused = false;
    exitGame = false;
}
