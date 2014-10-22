#pragma once

#include "../hitbox.hpp"
#include "../animation.hpp"

class AnimationHitbox : public Hitbox {
public:
    typedef Hitbox super;
    AnimationHitbox(const vec2f& position, Animation* animation);
    Animation* CurrentAnimation() const;
    Collision CollisionType(Rectangle* rectangle) const;

private:
    Animation* animation_;
};
