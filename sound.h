#ifndef SOUND_H
#define SOUND_H
#include<SFML/Audio.hpp>


class Sound
{


public:
    sf::Music music;
     std::vector<std::string> v_music;
    Sound(std::string &name);
    void Play_Sound();
    void Stop_Sound();
};

#endif // SOUND_H
