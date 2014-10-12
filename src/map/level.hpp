#pragma once

#include "tile_map.hpp"

class Level : public TileMap {
public:
    typedef TileMap super;
    Level(const char* map);
private:

};