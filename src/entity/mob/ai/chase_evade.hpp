#pragma once

#include "../ai.hpp"
#include "../../../map/path.hpp"
#include "wander.hpp"

class ChaseEvade : public AI {
public:
    typedef AI super;
    ChaseEvade(Mob* mob);

    void Update(double delta);
    void Debug() const;

private:
    Wander wander_;
};
