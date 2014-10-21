#include "attack.hpp"
#include "../../mob.hpp"

Attack::Attack(Mob* mob, const std::vector<SpriteSet*>& animations) : super("attack", mob, animations) {
}

void Attack::Enter() {
    super::Enter();

    hitbox_ = new AnimationHitbox(mob_->x(), mob_->y(), CurrentAnimation());
    mob_->Attach(hitbox_);
}

void Attack::Leave() {
    mob_->Detach(hitbox_);
    delete hitbox_;

    super::Leave();
}
