#include "item.hpp"
#include "../graphic/effect/float.hpp"

Item::Item(Sprite* sprite, float x, float y, const vec2f& offset) :
        super(sprite, x, y, offset)
{
    die_effect_ = new Float(25, 0.25);
}


bool Item::CanCollideWith(RectangleShape* rectangle) const {
    // Items are only collidable with the Player
    return !current_effect_ && rectangle->IsEntity() && ((Entity*) rectangle)->type() == PLAYER;
}

void Item::Damage(Entity* from, int damage) {
    if(CanCollideWith(from))
        HandleCollisionWith((Mob*)from);
}

void Item::Dead() {
    // Do nothing
}
