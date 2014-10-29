#include "../math/vec2.hpp"
#include "sprite.hpp"
#include <vector>

#pragma once

struct SpriteSet {
    std::vector<Sprite*> sprites;
    float width;
    float height;
    int idle_index;
    std::vector<int> intervals;
    vec2f position;
    bool ping_pong;

    SpriteSet(const std::vector<Sprite*>& sprites, int idle_index, int interval, const vec2f& position);
    SpriteSet(const std::vector<Sprite*>& sprites, int idle_index, const vec2f& position,
            const std::vector<int>& intervals);
};
