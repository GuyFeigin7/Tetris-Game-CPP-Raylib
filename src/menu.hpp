#pragma once

#include "raylib.h"
#include <vector>
#include <string>
#include "gameState.hpp"
#include "game.hpp"

class Menu
{
public:
    Menu(const std::vector<std::string>& menuOptions, Game& game);

    // Updates the menu by handling input
    void Update();

    // Renders the menu
    void Render();

    // Returns the currently selected option
    int GetSelectedOption() const;

    void DisplayScores();
    void DisplayControls();
    
    void Display();

private:
    std::vector<std::string> options;  // Stores menu options
    int selectedOption;                // Index of the selected option
    GameState gameState;
    Game& game;
};  
