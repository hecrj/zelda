#include "item.hpp"

Item::Item(Sprite* sprite, float x, float y) :
        super(0, sprite, x, y)
{}

bool Item::CanCollideWith(Rectangle* rectangle) const {
    // Items are only collidable with the Player
    return not effect_ and rectangle->IsEntity() and ((Entity*) rectangle)->type() == PLAYER;
}

void Item::Damage(Entity* from, int damage) {
    if(CanCollideWith(from))
        HandleCollisionWith((Mob*)from);
}
