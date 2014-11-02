#include "chase.hpp"
#include <iostream>

Chase::Chase(Mob* mob) :
        super(mob),
        direction_(Dir::random()),
        wander_(mob),
        period_duration_(50),
        current_duration_(0),
        alert(false),
        dying(false)
{}

bool Chase::Detected(Entity* destiny_entity){
    float diffX = mob_->position().x-destiny_entity->position().x;
    float diffY = mob_->position().y-destiny_entity->position().y;
    float diffXaux = (diffX>0)?diffX:-diffX;
    float diffYaux = (diffY>0)?diffY:-diffY;

    const Dir aux = mob_->facing();
    if (aux.vector().x==1 && diffYaux > diffXaux && diffX < 0)
        return true;
    else if (aux.vector().x==-1 && diffYaux > diffXaux && diffX > 0)
        return true;
    else if (aux.vector().y==-1 && diffXaux > diffYaux && diffY > 0)
        return true;
    else if (aux.vector().y==1 && diffXaux > diffYaux && diffY < 0)
        return true;
    else
        return false;
}

bool Chase::Lost(Entity* destiny_entity){
    float diffX = mob_->position().x-destiny_entity->position().x;
    float diffY = mob_->position().y-destiny_entity->position().y;

    const Dir aux = mob_->facing();
    if (aux.vector().x==1 && diffX > 0)
        return true;
    else if (aux.vector().x==-1 && diffX < 0)
        return true;
    else if (aux.vector().y==-1 && diffY < 0)
        return true;
    else if (aux.vector().y==1 && diffY > 0)
        return true;
    else
        return false;
}


Dir Chase::Evade(Dir aux){
    if (aux.vector().x==1)
        return Dir::UP;
    else if (aux.vector().x==-1)
        return Dir::DOWN;
    else if (aux.vector().y==1)
        return Dir::LEFT;
    else return Dir::RIGHT;
}

void Chase::Update(double delta) {
    Entity* destiny_entity = mob_->SeekPlayer();
    float diffX = mob_->position().x-destiny_entity->position().x;
    float diffY = mob_->position().y-destiny_entity->position().y;
    float diffXaux = (diffX>0)?diffX:-diffX;
    float diffYaux = (diffY>0)?diffY:-diffY;

    if (mob_->health() < 2)
        dying = true;

    if (!dying && (mob_->Distance(destiny_entity) > 150 || (!alert && !Detected(destiny_entity)) || (alert && Lost(destiny_entity)))){
        alert = false;
        wander_.Update(delta);
    }
    else{
        alert = true;
        if (current_duration_%10>0)
            --current_duration_;
        else if (current_duration_>0){
            if (!dying && diffYaux < mob_->height())
                direction_ = (dying)?((diffX>0)?Dir::RIGHT:Dir::LEFT):((diffX>0)?Dir::LEFT:Dir::RIGHT);
            else if (!dying && diffXaux < mob_->width())
                direction_ = (dying)?((diffX>0)?Dir::LEFT:Dir::RIGHT):((diffY>0)?Dir::UP:Dir::DOWN);
            /*if (diffYaux < mob_->height())
                direction_ = (diffX>0)?Dir::LEFT:Dir::RIGHT;
            else if (diffXaux < mob_->width())
                direction_ = (diffY>0)?Dir::UP:Dir::DOWN;*/
            --current_duration_;
        }
        else{
            std::cout << "hola" << std::endl;
            if (diffYaux < mob_->height())
                direction_ = (dying)?((diffX>0)?Dir::RIGHT:Dir::LEFT):((diffX>0)?Dir::LEFT:Dir::RIGHT);
            else if (diffXaux < mob_->width())
                direction_ = (dying)?((diffY>0)?Dir::DOWN:Dir::UP):((diffY>0)?Dir::UP:Dir::DOWN);
            else if (diffYaux > diffXaux/3.0f)
                direction_ = (dying)?((diffY>0)?Dir::DOWN:Dir::UP):((diffY>0)?Dir::UP:Dir::DOWN);
            else
                direction_ = (dying)?((diffX>0)?Dir::RIGHT:Dir::LEFT):((diffX>0)?Dir::LEFT:Dir::RIGHT);
            /*if (diffYaux < mob_->height())
                direction_ = (diffX>0)?Dir::LEFT:Dir::RIGHT;
            else if (diffXaux < mob_->width())
                direction_ = (diffY>0)?Dir::UP:Dir::DOWN;
            else if (diffYaux > diffXaux/3.0f)
                direction_ = (diffY>0)?Dir::UP:Dir::DOWN;
            else
                direction_ = (diffX>0)?Dir::LEFT:Dir::RIGHT;*/

            current_duration_ = period_duration_;
        }

        if (!mob_->Move(direction_,delta)){
            //mob_->Move(Contrary(direction_),delta);
            mob_->Move(Evade(direction_),delta);
        }
    }
}

void Chase::Debug() const {

}
