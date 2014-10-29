#pragma once

#include "tile_map.hpp"
#include "../entity.hpp"
#include "../entity/mob.hpp"
#include "location.hpp"
#include "path.hpp"
#include <set>
#include <queue>

class Level : public TileMap {
public:
    typedef TileMap super;

    static const int FOLLOW_MARGIN;
    static const int MAX_NODES_PER_TICK;

    Level(const char* map);

    Path* FindPath(Mob* from, Entity* to);
    const std::vector<Entity*>& players() const;

    bool transition_requested() const;
    void transition_data(std::string& map, std::string& place) const;

    void AddEntity(Entity* entity);
    void AddCollidable(Rectangle* rectangle);
    void AddLocation(Location* location);
    void CollidablesFor(Rectangle* rectangle, std::vector<Rectangle*>& collidables) const;
    void DynamicCollidablesFor(Rectangle* rectangle, std::vector<Rectangle*>& collidables) const;
    void AddPlayer(Entity* player, std::string location);
    void Transition(const std::string& map, const std::string& place);

    void Update(double delta);
    void Render();

private:
    vec2f position_;
    Entity* main_player_;
    std::vector<Entity*> players_;
    std::set<Entity*, Entity::SortByYCoordinateAsc> entities_;
    std::vector<Entity*> alive_entities_;
    std::vector<Entity*> zombies_;
    std::map<std::string, Location*> locations_;
    Quadtree* dynamic_collidables_;

    bool transition_requested_;
    std::string transition_map_;
    std::string transition_place_;

    // Pathfinding
    std::vector<std::vector<Path::Node*>> nodes_;
    std::list<Path*> pending_paths_;

    void CalculatePath();
    void RemovePendingPaths(Entity* entity);
};
