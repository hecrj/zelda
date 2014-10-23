#pragma once

#include "../graphic/animation.hpp"
#include "../math/rectangle.hpp"

class Hitbox : public Rectangle {
public:
    typedef Rectangle super;
    Hitbox(float x, float y, float width, float height);

    bool IsHitbox() const;
    virtual Sprite* CurrentSprite() const = 0;
    virtual Sprite* CurrentSprite(vec2f& sprite_position) const = 0;
};
