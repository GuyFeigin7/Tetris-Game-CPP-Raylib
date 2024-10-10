#include <iostream>
#include "raylib.h"
#include "game.hpp"
#include "colors.hpp"

int main ()
{
	Game game;
	game.Init(500, 620, 60, "Fonts/monogram.ttf", 64);
	game.Run();

	return 0;
}
