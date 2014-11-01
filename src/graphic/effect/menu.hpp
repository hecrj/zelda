#pragma once

#include "../effect.hpp"
#include "../../math/vec2.hpp"
#include <vector>
#include <functional>
#include <string>

class Menu : public Effect {
public:
    Menu(float x, float y, float separation);

    bool IsFinished() const;

    void Tick(double delta);
    void Render() const;

    void AddOption(const std::string& text, const std::function<void()> callback);

private:
    float x_;
    float y_;
    float separation_;

    struct MenuOption {
        std::string text;
        vec2f position;
        std::function<void()> callback;
    };
    std::vector<MenuOption> options_;
};
