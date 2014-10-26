#include <iostream>
#include "chase.hpp"

Chase::Chase(Mob* mob) :
        super(mob),
        wander_(mob),
        path_(0)
{}

void Chase::Move(double delta) {
    if(path_) {
        if(path_->ready) {
            mob_->FollowPath(path_, delta);

            if(not path_->Update(delta))
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
            Rectangle r(node->x * Path::RESOLUTION, node->y * Path::RESOLUTION,
                    Path::RESOLUTION, Path::RESOLUTION);
            r.Render(1, 1, 1);
        }
    }
}
