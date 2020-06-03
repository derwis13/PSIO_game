#include "sound.h"
#include <iostream>
Sound::Sound(std::string &name)
{
    music.openFromFile(name);
}

void Sound::Play_Sound()
{
    music.play();
}

void Sound::Stop_Sound()
{
    music.stop();
}
