#include "player.hpp"
#include "../../mob.hpp"
#include <GL/glut.h>

Player::Player(Mob* mob, bool* keys) : super(mob) {
    keys_ = keys;
}

void Player::Update(double delta) {
    if(keys_[GLUT_KEY_RIGHT])
        mob_->Move(Dir::RIGHT, delta);

    if(keys_[GLUT_KEY_LEFT])
        mob_->Move(Dir::LEFT, delta);

    if(keys_[GLUT_KEY_UP])
        mob_->Move(Dir::UP, delta);

    if(keys_[GLUT_KEY_DOWN])
        mob_->Move(Dir::DOWN, delta);
}
