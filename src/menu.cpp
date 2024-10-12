#include "menu.hpp"

Menu::Menu(const std::vector<std::string>& menuOptions, Game& newGame): options(menuOptions), 
                                                     selectedOption(0), 
                                                     gameState(GameState::MENU),
                                                     game(newGame)
{
    selectedOptionSound = LoadSound("Sounds/selectOption.mp3");
    enterSound = LoadSound("Sounds/enterSound.mp3");
}

Menu::~Menu()
{
    UnloadSound(selectedOptionSound);
    UnloadSound(enterSound);
}

void Menu::Update()
{
    if (IsKeyPressed(KEY_DOWN))
    {
        selectedOption = (selectedOption + 1) % options.size();
        PlaySound(selectedOptionSound);
    }
    else if (IsKeyPressed(KEY_UP))
    {
        selectedOption = (selectedOption - 1 + options.size()) % options.size();
        PlaySound(selectedOptionSound);
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
                PlaySound(enterSound);
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
            DrawText("Scores coming soon!", 50, 250, 40, WHITE);
            if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_ESCAPE))
            {
                gameState = GameState::MENU;  // Return to menu
            }
        }
        else if (gameState == GameState::EXIT)
        {
            break;  // Exit game
        }

        EndDrawing();
    }

    CloseWindow();
}

