#pragma once

#include <SFML/Audio/Sound.hpp>
#include <list>

class Sound {
public:
    static sf::SoundBuffer* Buffer(const char* file);
    static void Update(double delta);
    static void Play(sf::SoundBuffer* sound_buffer);

private:
    static const float GARBAGE_COLLECT_INTERVAL;
    static std::list<sf::Sound*> current_sounds_;
    static float accum_;
};
