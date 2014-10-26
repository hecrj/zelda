#include "chase.hpp"

Chase::Chase(Mob* mob) :
        super(mob),
        wander_(mob),
        path_(0)
{}

void Chase::Move(double delta) {
    if(not path_)
        path_ = FindPlayer();

    if(path_) {
        if(path_->ready) {
            if(not mob_->FollowPath(path_, delta))
                mob_->MoveTowards(path_->to, delta);
            UpdatePath(path_, delta);
        }
    } else {
        wander_.Move(delta);
    }
}

void Chase::Debug() const {
    if(path_)
        path_->Render();
}
