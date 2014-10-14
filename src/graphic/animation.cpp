#include "animation.hpp"

Animation::Animation(vec2f entity_position, int sprite_interval) {
    entity_position_ = entity_position;
    sprite_interval_ = sprite_interval;
    current_frame_ = 0;
}

int Animation::current_frame() const {
    return current_frame_;
}

void Animation::set_current_frame(int frame) {
    current_frame_ = frame;
}


void Animation::Update(double delta) {
    // TODO: Accumulate delta and increase current_frame accordingly
}
