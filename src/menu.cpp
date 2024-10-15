#include "menu.hpp"
#include "soundManager.hpp"

Menu::Menu(const std::vector<std::string>& menuOptions, Game& newGame): options(menuOptions), 
                                                     selectedOption(0), 
                                                     gameState(GameState::MENU),
                                                     game(newGame)
{}

void Menu::Update()
{
    if (IsKeyPressed(KEY_DOWN))
    {
        selectedOption = (selectedOption + 1) % options.size();
        SoundManager::GetInstance().PlaySelectedOptionSound();
    }
    else if (IsKeyPressed(KEY_UP))
    {
        selectedOption = (selectedOption - 1 + options.size()) % options.size();
        SoundManager::GetInstance().PlaySelectedOptionSound();
    }
}

void Menu::Render()
{
    for (int i = 0; i < options.size(); i++)
    {
        Color color = (i == selectedOption) ? GREEN : WHITE;
        DrawText(options[i].c_str(), 150, 200 + i * 50, 40, color);
    }
}

int Menu::GetSelectedOption() const
{
    return selectedOption;
}

void Menu::DisplayScores()
{
    DrawText("Scores coming soon!", 50, 250, 40, WHITE);

    if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_ESCAPE))
    {
        gameState = GameState::MENU;  // Return to menu
    }
}

void Menu::DisplayControls()
{
    DrawText("Move block left: Left arrow key", 50, 150, 25, WHITE);
    DrawText("Move block right: Right arrow key", 50, 200, 25, WHITE);
    DrawText("Move block down: Down arrow key", 50, 250, 25, WHITE);
    DrawText("Rotate block: Space", 50, 300, 25, WHITE);
    DrawText("Pause game: P", 50, 350, 25, WHITE);
    DrawText("Restart game: R", 50, 400, 25, WHITE);

    if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_ESCAPE))
    {
        gameState = GameState::MENU;  // Return to menu
    }
}

void Menu::Display()
{
    while (gameState != GameState::EXIT)
    {
        BeginDrawing();
        ClearBackground(BLACK);

        if (gameState == GameState::MENU)
        {
            Update();  // Handle input for the menu
            Render();  // Render the menu

            if (IsKeyPressed(KEY_ENTER))
            {
                SoundManager::GetInstance().PlayEnterSound();
                int selected = GetSelectedOption();
                if (selected == 0)
                {
                    gameState = GameState::PLAYING;  // Start game
                }
                else if (selected == 1)
                {
                    gameState = GameState::VIEW_SCORES;  // View scores
                }
                else if (selected == 2)
                {
                    gameState = GameState::VIEW_CONTROLS;
                }
                else if (selected == 3)
                {
                    gameState = GameState::EXIT;  // Exit game
                }
            }
        }
        else if (gameState == GameState::PLAYING)
        {
	        game.Run();
            gameState = GameState::MENU;
        }
        else if (gameState == GameState::VIEW_SCORES)
        {
            DisplayScores();
        }
        else if (gameState == GameState::VIEW_CONTROLS)
        {
            DisplayControls();
        }
        else if (gameState == GameState::EXIT)
        {
            break;  // Exit game
        }

        EndDrawing();
    }

    CloseWindow();
}

