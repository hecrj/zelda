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
            mob_->FollowPath(path_, delta);

            if(not path_->Update(delta)) {
                delete path_;
                path_ = FindPlayer();
            }
        }
    } else {
        wander_.Move(delta);
    }
}

void Chase::Debug() const {
    if(path_)
        path_->Render();
}
