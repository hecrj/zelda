#pragma once

#include "../object.hpp"

class Plant : public Object {
public:
    typedef Object super;
    Plant(Level* level, Sprite* sprite, float x, float y);

    void Dead();
};