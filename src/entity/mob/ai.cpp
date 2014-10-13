#include "ai.hpp"
#include "../mob.hpp"

AI::AI(Mob* mob) {
    mob_ = mob;
    mob->set_AI(this);
}
