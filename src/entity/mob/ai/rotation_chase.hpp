#pragma once

#include "../ai.hpp"

class RotationChase : public AI {
public:
    typedef AI super;
    RotationChase(Mob* mob);

    void Update(double delta);
};