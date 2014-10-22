#include <iostream>
#include "action.hpp"
#include "../mob.hpp"

Action::Action(Mob* mob, const std::vector<SpriteSet*>& spritesets) :
    mob_(mob)
{
    for(SpriteSet* spriteset : spritesets) {
        animations_.push_back(new Animation(spriteset));
    }
}

Action::Action(Mob* mob, const std::vector<Animation*>& animations) :
        mob_(mob),
        animations_(animations)
{}

bool Action::IsTemporary() const {
    return false;
}

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

const std::vector<Animation*>& Action::animations() const {
    return animations_;
}
