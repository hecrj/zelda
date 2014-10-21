#pragma once

#include "tile_map.hpp"
#include "../entity.hpp"
#include <set>

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
    struct YCoordinateCompare {
        bool operator() (Entity* e1, Entity* e2) const {
            return e1->y() < e2->y();
        }
    };

    std::set<Entity*, YCoordinateCompare> entities_;
    std::vector<Entity*> temp_entities_;
    Entity* player_;
};
