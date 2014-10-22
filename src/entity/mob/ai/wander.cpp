#include "wander.hpp"
#include "../../mob.hpp"

Wander::Wander(Mob* mob) :
        super(mob),
        accum(0),
        dir(Dir::random())
{}

void Wander::Move(double delta) {
    mob_->Move(dir, delta);
    accum += delta;

    if(accum > 0.5f) {
        dir = Dir::random();
        accum = 0;
    }
}

void Wander::Update(double delta) {

}
