#include <iostream>
#include "chase.hpp"
#include "../../../map/level.hpp"

Chase::Chase(Mob* mob) :
        super(mob),
        wander_(mob),
        path_(0)
{}

void Chase::Move(double delta) {
    if(path_) {
        if(path_->ready) {
            if(path_->Update(delta))
                mob_->FollowPath(path_);
            else
                SeekPlayer(delta);
        }
    } else {
        SeekPlayer(delta);
    }
}

void Chase::SeekPlayer(double delta) {
    Entity* player = mob_->SeekPlayer();

    if(player) {
        if(path_)
            delete path_;

        path_ = mob_->FindPath(player);
    } else {
        wander_.Move(delta);
    }
}

void Chase::Debug() const {
    if(path_ && path_->ready) {
        for(Path::Node* node : path_->nodes) {
            Rectangle r(node->x * Level::PATH_RESOLUTION, node->y * Level::PATH_RESOLUTION,
                    Level::PATH_RESOLUTION, Level::PATH_RESOLUTION);
            r.Render(1, 1, 1);
        }
    }
}
