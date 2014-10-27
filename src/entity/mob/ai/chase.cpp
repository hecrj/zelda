#include "chase.hpp"

Chase::Chase(Mob* mob) :
        super(mob),
        wander_(mob),
        path_(0)
{}

void Chase::Move(double delta) {
    if(not path_)
        path_ = FindPlayer();

    if(path_ and path_->ready) {
            if(not mob_->FollowPath(path_, delta))
                mob_->MoveTowards(path_->to, delta);

            if(not path_->Update(delta)) {
                delete path_;
                path_ = FindPlayer();
            }

    } else {
        wander_.Move(delta);
    }
}

void Chase::Debug() const {
    if(path_)
        path_->Render();
}
