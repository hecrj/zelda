#include "hidden_hitbox.hpp"

HiddenHitbox::HiddenHitbox(float x, float y, Animation* animation) :
        super(0, 0, animation->width(), animation->height())
{
    animation_ = animation;
    set_position(vec2f(x, y) + animation_->position());
}

Hitmap* HiddenHitbox::GetHitmap() const {
    return new Hitmap();
}
