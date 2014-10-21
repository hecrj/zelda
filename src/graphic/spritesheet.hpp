#include <vector>
#include <GL/gl.h>
#include "../math/vec2.hpp"
#include "animation.hpp"
#include "sprite.hpp"

#pragma once

class SpriteSheet {
public:
    SpriteSheet(const char* path, int width, int height, int sprite_width, int sprite_height);

    std::vector<Sprite*> GetSprites(int row, int sprite_count);

    void set_hit_spritesheet(const char* path);

private:
    GLuint texture_;
    int width_;
    int height_;
    int sprite_width_;
    int sprite_height_;
    float width_ratio_;
    float height_ratio_;
    SpriteSheet* hit_spritesheet_;
};
