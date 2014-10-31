#pragma once

#include "../callback_effect.hpp"
#include "../../map/tileset.hpp"
#include <vector>

class Overlay : public CallbackEffect {
public:
    typedef CallbackEffect super;
    Overlay(float duration, float x, float y, Tileset* tileset, const std::vector<std::vector<int>>& tiles,
            const std::function<void()>& callback);

    bool IsFinished() const;

    void Tick(double delta);
    void Render() const;

private:
    float duration_;
    float accum_;
    float x_;
    float y_;
    Tileset* tileset_;
    std::vector<std::vector<int>> tiles_;
};
