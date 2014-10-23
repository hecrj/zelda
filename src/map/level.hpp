#pragma once

#include "tile_map.hpp"
#include "../entity.hpp"
#include "../entity/mob.hpp"
#include <set>

class Level : public TileMap {
public:
    typedef TileMap super;
    Level(const char* map);

    void AddEntity(Entity* entity);
    void CollidablesFor(Rectangle* rectangle, std::vector<Rectangle*>& collidables) const;
    void DynamicCollidablesFor(Rectangle* rectangle, std::vector<Rectangle*>& collidables) const;
    void set_player(Entity* player);

    void Update(double delta);
    void Render();

private:
    struct YCoordinateCompare {
        bool operator() (Entity* e1, Entity* e2) const {
            if(e1->y() != e2->y())
                return e1->y() < e2->y();
            else
                return e1->x() < e2->x();
        }
    };

    std::set<Entity*, YCoordinateCompare> entities_;
    std::vector<Entity*> temp_entities_;
    Quadtree* dynamic_collidables_;
    Entity* player_;
};
