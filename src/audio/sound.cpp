#include <SFML/Audio/SoundBuffer.hpp>
#include "sound.hpp"
#include "../game.hpp"
#include <sstream>

const float Sound::GARBAGE_COLLECT_INTERVAL = 2.0f;
std::list<sf::Sound*> Sound::current_sounds_;
float Sound::accum_ = 0;

sf::SoundBuffer* Sound::Buffer(const char* file) {
    std::stringstream filename;
    filename << "res/sound/" << file;

    sf::SoundBuffer* buffer = new sf::SoundBuffer();

    if(! buffer->loadFromFile(filename.str()))
        Game::Error("Unable to load sound: ", filename.str());

    return buffer;
}

void Sound::Update(double delta) {
    accum_ += delta;

    if(accum_ >= GARBAGE_COLLECT_INTERVAL) {
        std::list<sf::Sound*>::iterator it = current_sounds_.begin();
        while(it != current_sounds_.end()) {
            sf::Sound* sound = *it;

            if(sound->getStatus() == sf::Sound::Stopped) {
                delete sound;
                it = current_sounds_.erase(it);
            } else {
                ++it;
            }
        }

        accum_ = 0;
    }
}

void Sound::Play(sf::SoundBuffer* sound_buffer) {
    if(sound_buffer) {
        sf::Sound* sound = new sf::Sound(*sound_buffer);
        sound->play();
        current_sounds_.push_back(sound);
    }
}
