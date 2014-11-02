#include "rotation_chase.hpp"

RotationChase::RotationChase(Mob* mob) :
        super(mob)
{}

void RotationChase::Update(double delta) {
    AI::Update(delta);
}
