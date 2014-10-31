#include "attack.hpp"
#include "../../mob.hpp"
#include "../../../audio/sound.hpp"

Attack::Attack(Mob* mob, const std::vector<SpriteSet*>& animations) : super(mob, animations) {
}

void Attack::Enter() {
    super::Enter();
    hitbox_ = new AnimationHitbox(mob_->position(), CurrentAnimation());
    Sound::Play(mob_->attack_sound());
}

void Attack::Update(double delta) {
    super::Update(delta);

    if(!IsFinished())
        mob_->MeleeAttack(hitbox_);
}

void Attack::Leave() {
    delete hitbox_;
    super::Leave();
}
