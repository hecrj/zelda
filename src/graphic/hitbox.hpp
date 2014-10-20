#include "../math/rectangle.hpp"
#include "../graphic/hitmap.hpp"

#pragma once

class Hitbox : public Rectangle {
public:
    typedef Rectangle super;
    Hitbox(float x, float y, float width, float height);

    virtual Hitmap* GetHitmap() const = 0;

    bool CollidesWith(Rectangle* r) const;
};
