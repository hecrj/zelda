#pragma once

#include "../ai.hpp"
#include "../../../map/path.hpp"
#include "wander.hpp"
#include <iostream>

class Follower : public AI {
public:
    typedef AI super;
    Follower(Mob* mob);

    void Update(double delta);
    void Debug() const;

private:
    Path* path_;
};
