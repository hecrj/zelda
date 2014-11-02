#include "follower.hpp"

Follower::Follower(Mob* mob) :
        super(mob),
        path_(0)
{}

void Follower::Update(double delta) {
    Entity* player = mob_->SeekPlayer();
    Entity* enemy_entity = mob_->SeekEnemy();
    if (mob_->Distance(player)<150 && enemy_entity){
        std::cout << "Checkpoint 0 dist: " << mob_->Distance(enemy_entity) << std::endl;
        if (mob_->Distance(enemy_entity) < 300){
            if (mob_->Distance(enemy_entity) < 34){
                float diffX = mob_->position().x-enemy_entity->position().x;
                float diffY = mob_->position().y-enemy_entity->position().y;
                float diffXaux = (diffX>0)?diffX:-diffX;
                float diffYaux = (diffY>0)?diffY:-diffY;

                Dir direct = mob_->facing();
                if (direct.vector().x==1 && diffYaux > diffXaux && diffX < 0)
                    direct = Dir::RIGHT;
                else if (direct.vector().x==-1 && diffYaux > diffXaux && diffX > 0)
                    direct = Dir::LEFT;
                else if (direct.vector().y==-1 && diffXaux > diffYaux && diffY > 0)
                    direct = Dir::UP;
                else if (direct.vector().y==1 && diffXaux > diffYaux && diffY < 0)
                    direct = Dir::DOWN;

                mob_->Move(direct,delta);
                mob_->ChangeAction(mob_->action("attack"));
            }
            else{
                if (not path_)
                    path_ = PathToEnemy();

                std::cout << "Checkpoint 1" << std::endl;
                if(path_ && path_->ready) {
                    std::cout << "Checkpoint 2" << std::endl;
                    mob_->FollowPath(path_, delta);

                    std::cout << "Checkpoint 3" << std::endl;
                    if(not path_->Update(delta) && mob_->Distance(path_->to) > 34) {
                        std::cout << "Checkpoint 4" << std::endl;
                        delete path_;
                        std::cout << "Checkpoint 5" << std::endl;
                        path_ = PathToEnemy();
                        std::cout << "Checkpoint 6" << std::endl;
                    }
                }
            }
        }
    }
    else{
        /*if(not path_)
            path_ = PathToPlayer();

        if(path_ && path_->ready) {
            mob_->FollowPath(path_, delta);

            if(not path_->Update(delta) && mob_->Distance(path_->to) > 50) {
                delete path_;
                path_ = PathToPlayer();
            }
        }*/

        std::cout << "Checkpoint 8" << std::endl;
        if(not path_)
            path_ = PathToPlayer();

        std::cout << "Checkpoint 9" << std::endl;
        if(path_){
            std::cout << "Checkpoint 9.1" << std::endl;
            if (path_->ready) {
                std::cout << "Checkpoint 10" << std::endl;
                mob_->FollowPath(path_, delta);
                std::cout << "Checkpoint 11" << std::endl;

                if(not path_->Update(delta)){
                    std::cout << "Checkpoint 11.1" << std::endl;
                    if (mob_->Distance(path_->to) > 50) {
                        std::cout << "Checkpoint 12" << std::endl;
                        delete path_;
                        path_ = PathToPlayer();
                    }
                }
            }
        }
    }
}

void Follower::Debug() const {
    if(path_)
        path_->Render();
}
