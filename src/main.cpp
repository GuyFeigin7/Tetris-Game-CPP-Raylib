#include <iostream>
#include "raylib.h"
#include "game.hpp"
#include "colors.hpp"
#include "menu.hpp"

int main ()
{
	InitAudioDevice();

	Game game;
	game.Init(500, 620, 60, "Fonts/monogram.ttf", 64);
	std::vector<std::string> menuOptions = {"Start Game", "View Scores", "Exit"};
    Menu menu(menuOptions, game);
	menu.Display();
	
	CloseAudioDevice();
	return 0;
}
