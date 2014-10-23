#include "level.hpp"
#include "../debug.hpp"
#include "../entity/map_object.hpp"

Level::Level(const char *map) : super(map)
{
    dynamic_collidables_ = new Quadtree(0, Rectangle(0, 0, map_->width_pixels, map_->height_pixels));

    for(const auto& k : map_->object_groups) {
        const TMX::ObjectGroup& object_group = k.second;

        for(const TMX::Object& object : object_group.object) {
            MapObject* map_object = new MapObject(tileset_, object.gid, object.x, object.y - 16, object.width, object.height);
            AddEntity(map_object);
        }
    }
}

void Level::Update(double delta) {
    for(Entity* entity : entities_) {
        if(entity->IsMob()) {
            dynamic_collidables_->Remove(entity);

            entity->Update(delta);

            if (entity->IsAlive()) {
                dynamic_collidables_->Insert(entity);
                temp_entities_.push_back(entity);
            } else if (entity != player_) {
                delete entity;
            }
        } else {
            if(entity->IsAlive()) {
                temp_entities_.push_back(entity);
            } else {
                dynamic_collidables_->Remove(entity);
                delete entity;
            }
        }
    }

    // We need to update the set in order to keep it sorted
    entities_.clear();
    entities_.insert(temp_entities_.begin(), temp_entities_.end());
    temp_entities_.clear();
}

void Level::Render() {
    super::RenderLayersBelow();

    for(Entity* entity : entities_) {
        entity->Render();
    }

    super::RenderLayersAbove();

    if(Debug::enabled) {
        dynamic_collidables_->Render(1, 0, 0);

        // Show collidable candidates
        std::vector<Rectangle*> candidates;

        for(Entity* entity : entities_) {
            if(entity->IsMob()) {
                static_collidables_->Retrieve(entity, candidates);
                dynamic_collidables_->Retrieve(entity, candidates);
            }
        }

        for(Rectangle* candidate : candidates)
            candidate->Render(1, 0.5, 0);
    }
}

void Level::AddEntity(Entity* entity) {
    entities_.insert(entity);
    dynamic_collidables_->Insert(entity);
}

void Level::AddMob(Mob* mob) {
    entities_.insert(mob);
    dynamic_collidables_->Insert(mob);
}

void Level::set_player(Entity* player) {
    player_ = player;
    AddEntity(player);
}

void Level::CollidablesFor(Rectangle* rectangle, std::vector<Rectangle*>& collidables) const {
    super::CollidablesFor(rectangle, collidables);
    dynamic_collidables_->Retrieve(rectangle, collidables);
}

void Level::DynamicCollidablesFor(Rectangle* rectangle, std::vector<Rectangle*>& collidables) const {
    dynamic_collidables_->Retrieve(rectangle, collidables);
}
