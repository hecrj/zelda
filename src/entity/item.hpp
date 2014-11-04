#pragma once

#include "object.hpp"

class Item : public Object {
public:
    typedef Object super;
    Item(Sprite* sprite, float x, float y, const vec2f& offset);

    bool CanCollideWith(RectangleShape* rectangle) const;

    void Damage(Entity* from, int damage);
    void Dead();
};
