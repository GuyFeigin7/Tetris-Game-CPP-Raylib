#include <fstream>
#include <iostream>
#include "game.hpp"

Game::Game() : blocks(GetAllBlocks()), 
               currentBlock(GetRandomBlock()), 
               nextBlock(GetRandomBlock()),
               score(0), 
               gameOver(false)
{
    InitAudioDevice();
    music = LoadMusicStream("Sounds/music.mp3");
    PlayMusicStream(music);
    rotateSound = LoadSound("Sounds/rotate.mp3");
    clearSound = LoadSound("Sounds/clear.mp3");
    gameOverSound = LoadSound("Sounds/gameover.wav");
}

Game::~Game()
{
    UnloadSound(rotateSound);
    UnloadSound(clearSound);
    UnloadSound(gameOverSound);
    UnloadMusicStream(music);
    CloseAudioDevice();
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
            nextBlock.Draw(255, 290);
            break;
        }
        case 4:
        {
            nextBlock.Draw(255, 280);
            break;
        }
        default:
        {
            nextBlock.Draw(270, 270);
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
                UpdateScore(0, 1);
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
            score += 100;
            break;
        }
        case 2:
        {
            score += 300;
            break;
        }
        case 3:
        {
            score += 500;
            break;
        }
    }

    score += moveDownPoints;

    if (score > GetHighestScore())
    {
        SaveHighestScore();
    }
}
