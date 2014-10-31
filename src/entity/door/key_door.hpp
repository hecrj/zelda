#pragma once

#include "../door.hpp"

class KeyDoor : public Door {
public:
    typedef Door super;
    KeyDoor(float x, float y, int tile_id, Tileset* tileset);

    bool HandleCollisionWith(Mob* mob);
};