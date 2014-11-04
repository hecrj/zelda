#pragma once

#include "../hitbox.hpp"
#include "../animation.hpp"

class AnimationHitbox : public Hitbox {
public:
    typedef Hitbox super;
    AnimationHitbox(const vec2f& position, Animation* animation);

    Sprite* CurrentSprite(vec2f& sprite_position) const;
    Sprite* CurrentSprite() const;
    Collision CollisionType(RectangleShape* rectangle) const;

private:
    Animation* animation_;
};
