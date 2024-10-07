#include <iostream>
#include "raylib.h"
#include "game.hpp"
#include "colors.hpp"

double G_LAST_UPDATE_TIME = 0;

static bool EventTriggered(double interval)
{
	double currentTime = GetTime();
	if (currentTime - G_LAST_UPDATE_TIME >= interval)
	{
		G_LAST_UPDATE_TIME = currentTime;
		return true;
	}
	return false;
}

int main ()
{
	InitWindow(500, 620, "Raylib Tetris");
	SetTargetFPS(60);

	Font font = LoadFontEx("Font/monogram/ttf", 64, 0, 0);

	Game game;

	while (!WindowShouldClose())
	{
		UpdateMusicStream(game.music);
		game.HandleInput();
		
		if (EventTriggered(0.2))
		{
			game.MoveBlockDown();
		}

		BeginDrawing();
		ClearBackground(darkBlue);
		DrawTextEx(font, "Score", {365, 15}, 38, 2, WHITE);
		DrawTextEx(font, "Next", {370, 175}, 38, 2, WHITE);
		if (game.gameOver)
		{
			DrawTextEx(font, "GAME OVER", {320, 520}, 29, 2, RED);
			DrawTextEx(font, "Press 'R' to\nrestart", {330, 565}, 20, 2, WHITE);
		}
		DrawRectangleRounded({320, 55,  170, 60}, 0.3, 6, lightBlue);

		char scoreText[10];
		sprintf(scoreText, "%d", game.score);
		Vector2 textSize = MeasureTextEx(font, scoreText, 38, 2);
		DrawTextEx(font, scoreText, {320 + (170 - textSize.x) / 2, 65}, 38, 2, WHITE);

		int highestScore = game.GetHighestScore();
		char highScoreText[10];
		sprintf(highScoreText, "%d", highestScore);
		Vector2 scoreTextSize = MeasureTextEx(font, highScoreText, 38, 2);
		DrawTextEx(font, "High Score", {320, 425}, 30, 2, YELLOW);
		DrawTextEx(font, highScoreText, {320 + (100 - scoreTextSize.x) / 2, 465}, 30, 2, WHITE);
		
		DrawRectangleRounded({320, 215,  170, 180}, 0.3, 6, lightBlue);
		game.Draw();
		EndDrawing();	
	}


	CloseWindow();

	return 0;
}
