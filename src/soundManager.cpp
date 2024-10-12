#include "soundManager.hpp"

SoundManager::SoundManager()
{
    music = LoadMusicStream("Sounds/music.mp3");
    PlayMusicStream(music);
    rotateSound = LoadSound("Sounds/rotate.mp3");
    clearSound = LoadSound("Sounds/clear.mp3");
    gameOverSound = LoadSound("Sounds/gameover.wav");
    levelUp = LoadSound("Sounds/levelup.mp3");
}

SoundManager::~SoundManager()
{
    UnloadSound(rotateSound);
    UnloadSound(clearSound);
    UnloadSound(gameOverSound);
    UnloadSound(levelUp);
    UnloadMusicStream(music);
}
