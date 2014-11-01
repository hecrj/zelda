#include "music.hpp"
#include "../game.hpp"
#include "../debug.hpp"
#include <sstream>
#include <iostream>

const bool Music::LOOP = true;
const bool Music::NO_LOOP = false;

std::queue<Music::MusicItem> Music::music_queue_;
sf::Music Music::music_;
float Music::accum_ = 0;
bool Music::fade_enabled_ = false;
float Music::fade_speed_ = 0;

void Music::Enqueue(const std::string& file, bool loop) {
    music_queue_.push(MusicItem(file, loop));
}

void Music::Update(double delta) {
    if(music_.getStatus() != sf::Music::Stopped) {
        if(fade_enabled_) {
            accum_ += delta;

            float volume = fade_speed_ * accum_;

            if(volume < 100.0f) {
                music_.setVolume(100.0f - volume);
            } else {
                fade_enabled_ = false;
                music_.stop();
                music_.setVolume(100.0f);
            }
        }
    } else if(not music_queue_.empty()) {
        const MusicItem& item = music_queue_.front();

        std::stringstream filename;
        filename << "res/music/" << item.first << ".ogg";

        if(! music_.openFromFile(filename.str()))
            Game::Error("Could not open music file:", filename.str());

        if(Debug::enabled)
            std::cout << "Playing music: " << filename.str() << std::endl;

        music_.setLoop(item.second);
        music_.play();
        fade_enabled_ = false;

        music_queue_.pop();
    }
}

void Music::FadeOut(float duration) {
    fade_enabled_ = true;
    fade_speed_ = 100.0f / duration;
}

void Music::ClearQueue() {
    music_queue_ = std::queue<MusicItem>();
}
