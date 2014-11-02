#include "wander.hpp"
#include "../../mob.hpp"

Wander::Wander(Mob* mob) :
        super(mob),
        accum(0),
        dir(Dir::random())
{}

void Wander::Update(double delta) {
    if (!mob_->Move(dir, delta))
        dir = Dir::random();

    accum += delta;

    if(accum > 0.5f) {
        dir = Dir::random();
        accum = 0;
    }
}
