#include <sstream>
#include <iostream>
#include "spritesheet.hpp"
#include "../utils.hpp"

SpriteSheet::SpriteSheet(const char* path, int width, int height, int sprite_width, int sprite_height) {
    texture_ = LoadTexture(path);
    width_ = width;
    height_ = height;
    sprite_width_ = sprite_width;
    sprite_height_ = sprite_height;
    width_ratio_ = (float)sprite_width / width;
    height_ratio_ = (float)sprite_height / height;
    hit_spritesheet_ = 0;
}

std::vector<Sprite*> SpriteSheet::GetSprites(int row, int sprite_count) const {
    std::vector<Sprite*> sprites;

    float y = row * height_ratio_;

    if(hit_spritesheet_) {
        const std::vector<Sprite*>& hit_sprites = hit_spritesheet_->GetSprites(row, sprite_count);

        for(int i = 0; i < sprite_count; ++i) {
            sprites.push_back(new Sprite(texture_, sprite_width_, sprite_height_,
                    i * width_ratio_, y, width_ratio_, height_ratio_, hit_sprites[i]->hit_map()));
        }
    } else {
        for(int i = 0; i < sprite_count; ++i) {
            sprites.push_back(new Sprite(texture_, sprite_width_, sprite_height_,
                    i * width_ratio_, y, width_ratio_, height_ratio_));
        }
    }

    return sprites;
}

void SpriteSheet::set_hit_spritesheet(char const* path) {
    hit_spritesheet_ = new SpriteSheet(path, width_, height_, sprite_width_, sprite_height_);
}
