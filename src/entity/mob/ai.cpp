#include "ai.hpp"
#include "../mob.hpp"
#include "../../map/path.hpp"
#include <iostream>

AI::AI(Mob* mob) {
    mob_ = mob;
}

void AI::Update(double delta) {
    // Do nothing
}

void AI::Debug() const {
    // Do nothing
}

Path* AI::PathToPlayer() const {
    Entity* player = mob_->SeekPlayer();

    if(player)
        return mob_->FindPath(player);

    return 0;
}

Path* AI::PathToEnemy() const {
    Entity* enemy = mob_->SeekEnemy();

    if(enemy){
        return mob_->FindPath(enemy);
    }

    return 0;
}
