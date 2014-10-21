#pragma once

#include "../hitbox.hpp"
#include "../animation.hpp"

class AnimationHitbox : public Hitbox {
public:
    typedef Hitbox super;
    AnimationHitbox(float x, float y, Animation* animation);

    Hitmap* GetHitmap() const;

private:
    Animation* animation_;
};
