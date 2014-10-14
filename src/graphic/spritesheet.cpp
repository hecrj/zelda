#include "spritesheet.hpp"

SpriteSheet::SpriteSheet(const char* path, int sprite_width, int sprite_height) {
    // TODO: Load path image

    sprite_width_ = sprite_width;
    sprite_height_ = sprite_height;
}

Animation* SpriteSheet::GetAnimation(int row, int sprite_count, int sprite_interval) {
    return GetAnimation(row, sprite_count, sprite_count, vec2f(0, 0));
}

Animation* SpriteSheet::GetAnimation(int row, int sprite_count, int sprite_interval, vec2f position) {
    Animation* animation = new Animation(position, sprite_interval);

    // TODO: Loop and process sprites of row
    // animation->AddSprite(...);

    return animation;
}
