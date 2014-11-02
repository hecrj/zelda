#include "key_door.hpp"
#include "../mob.hpp"
#include "../mob/link.hpp"

KeyDoor::KeyDoor(float x, float y, int tile_id, Tileset* tileset) :
        super(x, y, tile_id, tileset)
{}

bool KeyDoor::HandleCollisionWith(Mob* mob) {
    if(mob->type() == PLAYER) {
        Link* player = (Link*) mob;

        if(player->small_keys() > 0) {
            player->UpdateSmallKeys(-1);
            Open();
        }
    }

    return true;
}
