#include "follower.hpp"

Follower::Follower(Mob* mob) :
        super(mob),
        path_(0)
{}

void Follower::Update(double delta) {
    if(not path_)
        path_ = PathToPlayer();

    if(path_ && path_->ready) {
        mob_->FollowPath(path_, delta);

        if(not path_->Update(delta) && mob_->Distance(path_->to) > 50) {
            delete path_;
            path_ = PathToPlayer();
        }
    }
}

void Follower::Debug() const {
    if(path_)
        path_->Render();
}
