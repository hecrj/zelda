#include "chase_evade.hpp"

ChaseEvade::ChaseEvade(Mob* mob) :
        super(mob),
        wander_(mob)
{}

void ChaseEvade::Update(double delta) {
    wander_.Update(delta);
}

void ChaseEvade::Debug() const {
    AI::Debug();
}
