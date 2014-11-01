#pragma once

#include "../effect.hpp"
#include "../../math/vec2.hpp"
#include <vector>
#include <functional>
#include <string>
#include <SFML/Audio/SoundBuffer.hpp>

class Menu : public Effect {
public:
    static sf::SoundBuffer* MOVE_CURSOR_SOUND;
    static sf::SoundBuffer* SELECT_SOUND;

    Menu(float x, float y, float separation);

    bool IsFinished() const;

    void Tick(double delta);
    void Render() const;

    void AddOption(const std::string& text, const std::function<void()> callback);

private:
    float x_;
    float y_;
    float separation_;
    int selected_;

    struct MenuOption {
        std::string text;
        vec2f position;
        std::function<void()> callback;
    };
    std::vector<MenuOption> options_;
};
