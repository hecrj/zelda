#include <SOIL.h>
#include <sstream>
#include <iostream>
#include "spritesheet.hpp"

SpriteSheet::SpriteSheet(const char* path, int width, int height, int sprite_width, int sprite_height) {
    std::stringstream resource_path;
    resource_path << "res/" << path;

    texture_ = SOIL_load_OGL_texture(resource_path.str().c_str(),
            SOIL_LOAD_RGBA,
            SOIL_CREATE_NEW_ID,
            SOIL_FLAG_MULTIPLY_ALPHA);

    // This avoids blurry sprites (we like retro style)
    glBindTexture(GL_TEXTURE_2D, texture_);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glBindTexture(GL_TEXTURE_2D, 0);

    sprite_width_ = sprite_width;
    sprite_height_ = sprite_height;
    width_ratio_ = (float)sprite_width / width;
    height_ratio_ = (float)sprite_height / height;
}

std::vector<Sprite*> SpriteSheet::GetSprites(int row, int sprite_count) {
    std::vector<Sprite*> sprites;

    float y = row * height_ratio_;

    for(int i = 0; i < sprite_count; ++i) {
        sprites.push_back(new Sprite(texture_, sprite_width_, sprite_height_,
                i * width_ratio_, y, width_ratio_, height_ratio_));
    }

    return sprites;
}
