#pragma once

#include "object.hpp"

class Item : public Object {
public:
    typedef Object super;
    Item(Sprite* sprite, float x, float y);

    bool CanCollideWith(Rectangle* rectangle) const;
};
