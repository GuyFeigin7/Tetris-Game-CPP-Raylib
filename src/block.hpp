#pragma once

#include <vector>
#include <map>
#include "position.hpp"
#include "colors.hpp"

// Represents a single block in the Tetris game.
class Block
{
public:
    Block();

    // Draws the block on the screen with a specified offset.
    void Draw(int offsetX, int offsetY);

    // Moves the block by a specified number of rows and columns
    void Move(int rows, int cols);

    // Returns the positions of the cells occupied by the block.
    std::vector<Position> GetCellPositions();

    // Rotates the block to its next rotation state.
    void Rotate();

    // Reverts the block to its previous rotation state.
    void UndoRotation();
    
    int id; //Unique identifier for the block.
    std::map<int, std::vector<Position>> cells; // Maps rotation state to block cell positions.

private:
    int cellSize;
    int rotationState;
    int rowOffset;
    int columnOffset;
    std::vector<Color> colors; // Colors used for rendering the block.
};