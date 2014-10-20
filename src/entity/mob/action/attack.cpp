#include "attack.hpp"
#include "../../mob.hpp"

Attack::Attack(Mob* mob, const std::vector<Animation*>& animations) : super("attack", mob, animations) {

}

void Attack::Update(double delta) {
    // Do pixel perfect colision check

    super::Update(delta);
}
