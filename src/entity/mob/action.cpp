#include "action.hpp"

Action::Action(const char* name) {

}


bool Action::isBlocking() const {
    return true;
}

bool Action::isFinished() const {
    return false;
}

void Action::Enter() {

}

void Action::Leave() {

}

void Action::Update(float delta) {
    // TODO: Update animation
}

void Action::Render() const {
    // TODO: Render animation
}