#include "boss_door.hpp"
#include "../mob.hpp"
#include "../mob/link.hpp"

BossDoor::BossDoor(float x, float y, int tile_id, Tileset* tileset) :
        super(x, y, tile_id, tileset)
{}

bool BossDoor::HandleCollisionWith(Mob* mob) {
    if(mob->type() == PLAYER) {
        Link* player = (Link*) mob;

        if(player->boss_keys() > 0) {
            player->UpdateBossKeys(-1);
            Open();
        }
    }

    return true;
}
