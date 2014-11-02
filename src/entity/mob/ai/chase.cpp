#include "chase.hpp"

Chase::Chase(Mob* mob) :
        super(mob),
        direction_(Dir::random()),
        wander_(mob),
        period_duration_(50),
        current_duration_(0),
        alert(false)
{}

void Chase::Update(double delta) {
    wander_.Update(delta);
}

void Chase::Debug() const {

}
