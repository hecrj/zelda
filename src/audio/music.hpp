#pragma once

#include <SFML/Audio/Music.hpp>
#include <queue>

class Music {
public:
    typedef std::pair<std::string, bool> MusicItem;
    static const bool LOOP;
    static const bool NO_LOOP;

    static void Enqueue(const std::string& file, bool loop);
    static void Update(double delta);
    static void FadeOut(float duration);

    static void ClearQueue();

private:
    static std::queue<MusicItem> music_queue_;
    static sf::Music music_;
    static float accum_;
    static bool fade_enabled_;
    static float fade_speed_;
};
