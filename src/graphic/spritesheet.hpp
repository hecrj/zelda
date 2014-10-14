#include <vector>
#include "../math/vec2.hpp"
#include "animation.hpp"
#include "sprite.hpp"

#pragma once

class SpriteSheet {
public:
    SpriteSheet(const char* path, int sprite_width, int sprite_height);

    std::vector<Sprite*> GetSprites(int row, int sprite_count);

private:
    // TODO: Complete this class
    int sprite_width_;
    int sprite_height_;
};
