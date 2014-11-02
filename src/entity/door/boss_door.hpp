#pragma once

#include "../door.hpp"

class BossDoor : public Door {
public:
    typedef Door super;
    BossDoor(float x, float y, int tile_id, Tileset* tileset);

    bool HandleCollisionWith(Mob* mob);
};
