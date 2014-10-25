#pragma once

#include "tile_map.hpp"
#include "../entity.hpp"
#include "../entity/mob.hpp"
#include "path.hpp"
#include <set>
#include <queue>

class Level : public TileMap {
public:
    typedef TileMap super;

    static const int PATH_RESOLUTION;
    static const int FOLLOW_MARGIN;

    Level(const char* map);

    Path* FindPath(Mob* from, Entity* to);
    const std::vector<Entity*>& players() const;

    void AddEntity(Entity* entity);
    void CollidablesFor(Rectangle* rectangle, std::vector<Rectangle*>& collidables) const;
    void DynamicCollidablesFor(Rectangle* rectangle, std::vector<Rectangle*>& collidables) const;
    void AddPlayer(Entity* player);

    void Update(double delta);
    void Render();

private:
    vec2f position_;
    Entity* main_player_;
    std::vector<Entity*> players_;
    std::set<Entity*, Entity::SortByYCoordinateAsc> entities_;
    std::vector<Entity*> temp_entities_;
    Quadtree* dynamic_collidables_;

    // Pathfinding
    std::vector<std::vector<Path::Node*>> nodes_;
    std::queue<Path*> path_queue_;

    void CalculatePath();
};
