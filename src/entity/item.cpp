#include "item.hpp"

Item::Item(Sprite* sprite, float x, float y) :
        super(0, sprite, x, y)
{}

bool Item::CanCollideWith(Rectangle* rectangle) const {
    // Items are only collidable with the Player
    return rectangle->IsEntity() and ((Entity*) rectangle)->type() == PLAYER;
}
