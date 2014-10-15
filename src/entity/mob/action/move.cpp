#include "move.hpp"
#include "../../mob.hpp"

Move::Move(Mob* mob, const std::vector<Animation*>& animations) : super("move", mob, animations) {

}

bool Move::IsBlocking() const {
    return false;
}

void Move::Update(double delta) {
    if(mob_->moving()) {
        super::Update(delta);
    } else {
        CurrentAnimation()->Reset();
    }
}
