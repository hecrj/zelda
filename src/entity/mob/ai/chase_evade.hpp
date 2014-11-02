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
    bool Detected(Entity* destiny_entity);
    bool Lost(Entity* destiny_entity);

    Dir Contrary(Dir aux);

    Dir Evade(Dir aux);

private:
    Wander wander_;
    Dir direction_;
    unsigned int period_duration_;
    unsigned int current_duration_;
    bool alert;
};
