#pragma once

#include "../object.hpp"

class Plant : public Object {
public:
    typedef Object super;
    Plant(Sprite* sprite, float x, float y);
};