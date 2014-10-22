#include "../math/rectangle.hpp"
#include "animation.hpp"

#pragma once

class Hitbox : public Rectangle {
public:
    typedef Rectangle super;
    Hitbox(float x, float y, float width, float height);

    bool IsHitbox() const;
    virtual Animation* CurrentAnimation() const = 0;
};
