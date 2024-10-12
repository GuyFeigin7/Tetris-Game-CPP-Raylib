#pragma once

#include <raylib.h>

class SoundManager
{
public:
    SoundManager();
    ~SoundManager();

    Sound rotateSound;
    Sound clearSound;
    Sound gameOverSound;
    Sound levelUp;
    Music music;
    
private:
};