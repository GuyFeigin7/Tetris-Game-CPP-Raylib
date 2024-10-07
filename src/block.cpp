#include "block.hpp"

Block::Block() : cellSize(30), 
                 rotationState(0), 
                 rowOffset(0), 
                 columnOffset(0), 
                 colors(GetCellColors())
{}

void Block::Draw(int offsetX, int offsetY)
{
    std::vector<Position> tiles = GetCellPositions();
    for (Position item: tiles)
    {
        DrawRectangle(item.col * cellSize + offsetX, item.row * cellSize + offsetY, cellSize - 1, cellSize - 1, colors[id]);
    }
}

void Block::Move(int rows, int cols)
{
    rowOffset += rows;
    columnOffset += cols;
}

std::vector<Position> Block::GetCellPositions()
{
    std::vector<Position> tiles = cells[rotationState];
    std::vector<Position> movedTiles;

    for (Position item : tiles)
    {
        Position newPos = Position(item.row + rowOffset, item.col + columnOffset);
        movedTiles.push_back(newPos);
    }

    return movedTiles;
}

void Block::Rotate()
{
    ++rotationState;
    if (rotationState == static_cast<int>(cells.size()))
    {
        rotationState = 0;
    }
}

void Block::UndoRotation()
{
    --rotationState;
    if (rotationState < 0)
    {
        rotationState = static_cast<int>(cells.size() - 1);
    }
}
