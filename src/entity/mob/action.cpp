#include <GL/gl.h>
#include <iostream>
#include "action.hpp"
#include "../mob.hpp"

Action::Action(const char* name, Mob* mob, const std::vector<Animation*>& animations) {
    name_ = name;
    mob_ = mob;
}


bool Action::IsBlocking() const {
    return true;
}

bool Action::IsFinished() const {
    return false;
}

void Action::Enter() {

}

void Action::Leave() {

}

void Action::Update(double delta) {
    // TODO: Update animation
}

void Action::Render() const {
    // TODO: Render animation
    // We draw a red rectangle now for debugging purposes
    vec2f top_left = mob_->top_left();
    vec2f bottom_right = mob_->bottom_right();

    glColor4f(1, 0, 0, 1);
    glBegin(GL_QUADS);

    glVertex2f(top_left.x, top_left.y);
    glVertex2f(bottom_right.x, top_left.y);
    glVertex2f(bottom_right.x, bottom_right.y);
    glVertex2f(top_left.x, bottom_right.y);

    glEnd();
    glColor4f(1, 1, 1, 1);
}
