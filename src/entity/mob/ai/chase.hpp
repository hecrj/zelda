#pragma once

#include "../ai.hpp"
#include "../../../map/path.hpp"
#include "wander.hpp"

class Chase : public AI {
public:
    typedef AI super;
    Chase(Mob* mob);

    void Update(double delta);
    void Debug() const;
    bool Detected(Entity* destiny_entity);
    bool Lost(Entity* destiny_entity);


private:
    Wander wander_;
    Dir direction_;
    unsigned int period_duration_;
    unsigned int current_duration_;
    bool alert;
};
