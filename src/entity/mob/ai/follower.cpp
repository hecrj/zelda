#include "follower.hpp"

Follower::Follower(Mob* mob) :
        super(mob),
        path_(0)
{}

void Follower::Update(double delta) {
    Entity* player = mob_->SeekPlayer();
    Entity* enemy_entity = mob_->SeekEnemy();
    if (mob_->Distance(player)<150 && enemy_entity){
        std::cout << "Checkpoint2.1" << std::endl;
        if (mob_->Distance(enemy_entity) < 300){
            std::cout << "Checkpoint2.2" << std::endl;
            if (mob_->Distance(enemy_entity) < 34){
                std::cout << "Checkpoint2.3" << std::endl;
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
                std::cout << "Checkpoint2.4" << std::endl;
                if (not path_)
                    path_ = PathToEnemy();

                if(path_ && path_->ready) {
                    std::cout << "Checkpoint2.5" << std::endl;
                    mob_->FollowPath(path_, delta);

                    if(not path_->Update(delta) && mob_->Distance(path_->to) > 34) {
                        std::cout << "Checkpoint2.6" << std::endl;
                        delete path_;
                        path_ = PathToEnemy();
                    }
                }
            }
        }
    } else{
        std::cout << "Distancia2: " << mob_->Distance(player) << std::endl;

        if(not path_){
            std::cout << "Checkpoint1.0" << std::endl;
            path_ = PathToPlayer();
        }

        if(path_){
            std::cout << "Checkpoint1.1" << std::endl;
            if (path_->ready) {
                mob_->FollowPath(path_, delta);
                std::cout << "Checkpoint1.2" << std::endl;

                if(not path_->Update(delta)){
                    std::cout << "Checkpoint1.3" << std::endl;
                    if (mob_->Distance(path_->to) > 50) {
                        std::cout << "Checkpoint1.4" << std::endl;
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
