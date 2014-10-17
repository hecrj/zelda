#pragma once

#include "tile_map.hpp"
#include "../entity.hpp"
#include <vector>

class Level : public TileMap {
public:
    typedef TileMap super;
    Level(const char* map);

    void AddEntity(Entity* entity);
    void set_player(Entity* player);

    void Update(double delta);
    void Render();

private:
    std::vector<Entity*> entities_;
    Entity* player_;
};
