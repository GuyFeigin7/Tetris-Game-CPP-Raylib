#include "raylib.h"
#include <fstream>
#include <iostream>
#include "game.hpp"

Game::Game() : blocks(GetAllBlocks()), 
               currentBlock(GetRandomBlock()), 
               nextBlock(GetRandomBlock()),
               score(0), 
               gameOver(false),
               lastUpdateTime(0),
               difficulty(0.3),
               difficultyFactor(1),
               nextDifficulty(1000),
               maxDifficulty(64000),
               difficultyNum(1)
{
    InitAudioDevice();
    music = LoadMusicStream("Sounds/music.mp3");
    PlayMusicStream(music);
    rotateSound = LoadSound("Sounds/rotate.mp3");
    clearSound = LoadSound("Sounds/clear.mp3");
    gameOverSound = LoadSound("Sounds/gameover.wav");
    levelUp = LoadSound("Sounds/levelup.mp3");
}

Game::~Game()
{
    UnloadSound(rotateSound);
    UnloadSound(clearSound);
    UnloadSound(gameOverSound);
    UnloadSound(levelUp);
    UnloadMusicStream(music);
    CloseAudioDevice();
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
		UpdateMusicStream(music);
		HandleInput();
		
		if (EventTriggered(difficulty))
		{
			MoveBlockDown();
		}

		BeginDrawing();
		ClearBackground(darkBlue);
		DrawTextEx(font, "Score", {365, 15}, 38, 2, WHITE);
        DrawTextEx(font, "Difficulty", {330, 125}, 28, 2, GREEN);
        DrawRectangleRounded({320, 160,  170, 60}, 0.3, 6, lightBlue);

        char difficultyText[10];
		sprintf(difficultyText, "%d", difficultyNum);
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
		sprintf(scoreText, "%d", score);
		Vector2 textSize = MeasureTextEx(font, scoreText, 38, 2);
		DrawTextEx(font, scoreText, {320 + (170 - textSize.x) / 2, 65}, 38, 2, WHITE);

		int highestScore = GetHighestScore();
		char highScoreText[10];
		sprintf(highScoreText, "%d", highestScore);
		Vector2 scoreTextSize = MeasureTextEx(font, highScoreText, 38, 2);
		DrawTextEx(font, "High Score", {320, 425}, 30, 2, YELLOW);
		DrawTextEx(font, highScoreText, {320 + (185 - scoreTextSize.x) / 2, 465}, 30, 2, WHITE);
		
		DrawRectangleRounded({320, 280,  170, 140}, 0.3, 6, lightBlue); //Next block rectangle
		Draw();

		EndDrawing();	
	}

    CloseWindow();
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
    int keyPressed = GetKeyPressed();
    if (gameOver && keyPressed == KEY_R)
    {
        gameOver = false;
        Reset();
    }

    switch (keyPressed)
    {
        case KEY_LEFT:
        {
            MoveBlockLeft();
            break;
        }
        case KEY_RIGHT:
        {
            MoveBlockRight();
            break;
        }
        case KEY_DOWN:
        {
            MoveBlockDown();
            if (!gameOver)
            {
                UpdateScore(0, 5);
            }
            break;
        }
        case KEY_SPACE:
        {
            RotateBlock();
            break;
        }
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

void Game::SaveHighestScore()
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

void Game::UpdateDifficulty()
{
    if (score >= nextDifficulty && score <= maxDifficulty)
    {
        difficulty = difficulty * 0.9;
        nextDifficulty *= 2;
        difficultyFactor += 0.5;
        ++difficultyNum;
        PlaySound(levelUp);
    }
}

int Game::GetHighestScore()
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
            PlaySound(rotateSound);
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
        PlaySound(gameOverSound);
    }

    nextBlock = GetRandomBlock();
    int rowsCleared = grid.ClearFullRows();
    if (rowsCleared > 0)
    {
        PlaySound(clearSound);
        UpdateScore(rowsCleared, 0);
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
    score = 0;
}

void Game::UpdateScore(int linesCleared, int moveDownPoints)
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

    UpdateDifficulty();
}
