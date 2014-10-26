#include "ai.hpp"
#include "../mob.hpp"
#include "../../map/path.hpp"

AI::AI(Mob* mob) {
    mob_ = mob;
}

void AI::Update(double delta) {
    // Do nothing
}

void AI::Move(double delta) {
    // Do nothing
}

void AI::Debug() const {
    // Do nothing
}

Path* AI::FindPlayer() const {
    Entity* player = mob_->SeekPlayer();

    if(player)
        return mob_->FindPath(player);

    return 0;
}
