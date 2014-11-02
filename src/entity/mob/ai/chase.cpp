#include "chase.hpp"

Chase::Chase(Mob* mob) :
        super(mob),
        wander_(mob)
{}

void Chase::Update(double delta) {
    wander_.Update(delta);
}

void Chase::Debug() const {

}
