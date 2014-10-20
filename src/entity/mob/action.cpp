#include <iostream>
#include "action.hpp"
#include "../mob.hpp"

Action::Action(const char* name, Mob* mob, const std::vector<Animation*>& animations) :
    name_(name),
    mob_(mob),
    animations_(animations)
{}

bool Action::IsBlocking() const {
    return true;
}

bool Action::IsFinished() const {
    return animations_[mob_->facing().index()]->IsFinished();
}

Animation* Action::CurrentAnimation() const {
    return animations_[mob_->facing().index()];
}

void Action::Enter() {

}

void Action::Leave() {
    CurrentAnimation()->Reset();
}

void Action::Update(double delta) {
    CurrentAnimation()->Update(delta);
}

void Action::Render() const {
    CurrentAnimation()->Render(mob_->position());
}
