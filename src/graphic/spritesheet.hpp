#include <vector>
#include "../math/vec2.hpp"
#include "animation.hpp"

#pragma once

class SpriteSheet {
public:
    SpriteSheet(const char* path, int sprite_width, int sprite_height);

    // TODO: GetSprite(int i, int j) method
    Animation* GetAnimation(int row, int sprite_count, int sprite_interval);
    Animation* GetAnimation(int row, int sprite_count, int sprite_interval, vec2f position);

private:
    // TODO: Complete this class
    int sprite_width_;
    int sprite_height_;
};
