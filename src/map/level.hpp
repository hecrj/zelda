#pragma once

#include "tile_map.hpp"
#include "../entity.hpp"
#include <list>

class Level : public TileMap {
public:
    typedef TileMap super;
    Level(const char* map);

    void AddEntity(Entity* entity);
    void AddCollidable(Rectangle* rectangle);
    void RemoveCollidable(Rectangle* rectangle);
    void set_player(Entity* player);

    void Update(double delta);
    void Render();

private:
    std::list<Entity*> entities_;
    Entity* player_;
};
