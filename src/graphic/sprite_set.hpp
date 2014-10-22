#include "../math/vec2.hpp"
#include "sprite.hpp"
#include <vector>

#pragma once

struct SpriteSet {
    std::vector<Sprite*> sprites;
    float width;
    float height;
    int idle_index;
    // TODO: Support different intervals per sprite
    int interval;
    vec2f position;
    bool ping_pong;

    SpriteSet(const std::vector<Sprite*>& sprites, int idle_index, int interval);
    SpriteSet(const std::vector<Sprite*>& sprites, int idle_index, int interval, vec2f position);
};
