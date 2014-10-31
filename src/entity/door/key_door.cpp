#include "key_door.hpp"
#include "../mob.hpp"

KeyDoor::KeyDoor(float x, float y, int tile_id, Tileset* tileset) :
        super(x, y, tile_id, tileset)
{}

bool KeyDoor::HandleCollisionWith(Mob* mob) {
    if(mob->type() == PLAYER) {
        Open();
    }

    return true;
}
