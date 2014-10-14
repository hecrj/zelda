#include "spritesheet.hpp"

SpriteSheet::SpriteSheet(const char* path, int sprite_width, int sprite_height) {
    // TODO: Load path image

    sprite_width_ = sprite_width;
    sprite_height_ = sprite_height;
}

std::vector<Sprite*> SpriteSheet::GetSprites(int row, int sprite_count) {
    std::vector<Sprite*> sprites;

    // TODO: Loop and process sprites of row
    // ...
    // sprites.push_back(sprite);
    // ...

    return sprites;
}
