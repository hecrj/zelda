#include "item.hpp"
#include "../graphic/effect/float.hpp"

Item::Item(Sprite* sprite, float x, float y, const vec2f& offset) :
        super(sprite, x, y, offset)
{
    die_effect_ = new Float(this, 25, 0.25);
}


bool Item::CanCollideWith(Rectangle* rectangle) const {
    // Items are only collidable with the Player
    return not current_effect_ and rectangle->IsEntity() and ((Entity*) rectangle)->type() == PLAYER;
}

void Item::Damage(Entity* from, int damage) {
    if(CanCollideWith(from))
        HandleCollisionWith((Mob*)from);
}
