#pragma once

#include <raylib.h>

class SoundManager
{
public:
    // Method to get the single instance of the SoundManager
    static SoundManager& GetInstance();

    SoundManager(const SoundManager& other) = delete;
    SoundManager& operator=(const SoundManager& other) = delete;

    void PlayRotateSound();
    void PlayClearSound();
    void PlayGameOverSound();
    void PlayLevelUpSound();
    void PlaySelectedOptionSound();
    void PlayEnterSound();
    void ResetMusic();
    void StopMusic();
    void PlayMusic();

private:
    SoundManager();
    ~SoundManager();

    Sound rotateSound;
    Sound clearSound;
    Sound gameOverSound;
    Sound levelUpSound;
    Sound selectedOptionSound;
    Sound enterSound;
    Music music;
};