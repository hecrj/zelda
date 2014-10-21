#include "animation_hitbox.hpp"

AnimationHitbox::AnimationHitbox(float x, float y, Animation* animation) :
        super(0, 0, animation->width(), animation->height())
{
    animation_ = animation;
    set_position(vec2f(x, y) + animation_->position());
}

Hitmap*AnimationHitbox::GetHitmap() const {
    return animation_->CurrentHitmap();
}
