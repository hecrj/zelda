#include "animation.hpp"

Animation::Animation(const std::vector<Sprite*>& sprites, int sprite_interval, vec2f position) {
    sprites_ = sprites;
    position_ = position;
    sprite_interval_ = sprite_interval;
    current_frame_ = 0;
}

Animation::Animation(const std::vector<Sprite*>& sprites, int sprite_interval) :
        Animation(sprites, sprite_interval, vec2f(0, 0))
{}


int Animation::current_frame() const {
    return current_frame_;
}

void Animation::set_current_frame(int frame) {
    current_frame_ = frame;
}


void Animation::Update(double delta) {
    // TODO: Accumulate delta and increase current_frame accordingly
}
