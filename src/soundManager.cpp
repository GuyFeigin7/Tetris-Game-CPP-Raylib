#include "soundManager.hpp"

SoundManager::SoundManager()
{
    rotateSound = LoadSound("Sounds/rotate.mp3");
    clearSound = LoadSound("Sounds/clear.mp3");
    gameOverSound = LoadSound("Sounds/gameover.wav");
    levelUpSound = LoadSound("Sounds/levelup.mp3");
    selectedOptionSound = LoadSound("Sounds/selectOption.mp3");
    enterSound = LoadSound("Sounds/enterSound.mp3");
    music = LoadMusicStream("Sounds/music.mp3");
    ResetMusic();
}

SoundManager::~SoundManager()
{
    UnloadSound(rotateSound);
    UnloadSound(clearSound);
    UnloadSound(gameOverSound);
    UnloadSound(levelUpSound);
    UnloadSound(selectedOptionSound);
    UnloadSound(enterSound);
    UnloadMusicStream(music);
}

SoundManager &SoundManager::GetInstance()
{
        // Guaranteed to be created once and only once
        static SoundManager instance;
        return instance;
}

void SoundManager::PlayRotateSound()
{
    PlaySound(rotateSound);
}

void SoundManager::PlayClearSound()
{
    PlaySound(clearSound);

}

void SoundManager::PlayGameOverSound()
{
    PlaySound(gameOverSound);
}

void SoundManager::PlayLevelUpSound()
{
    PlaySound(levelUpSound);
}

void SoundManager::ResetMusic()
{
    PlayMusicStream(music);
}

void SoundManager::PlaySelectedOptionSound()
{
    PlaySound(selectedOptionSound);
}

void SoundManager::PlayEnterSound()
{
    PlaySound(enterSound);
}

void SoundManager::StopMusic()
{
    StopMusicStream(music);
}

void SoundManager::PlayMusic()
{
    UpdateMusicStream(music);
}
