#include "level.hpp"
#include "../debug.hpp"

Level::Level(const char *map) : super(map)
{
    dynamic_collidables_ = new Quadtree(0, Rectangle(0, 0, map_->width_pixels, map_->height_pixels));
}

void Level::Update(double delta) {
    for(Entity* entity : entities_) {
        dynamic_collidables_->Remove(entity);

        entity->Update(delta);

        if(entity->IsAlive()) {
            dynamic_collidables_->Insert(entity);
            temp_entities_.push_back(entity);
        } else if(entity != player_) {
            delete entity;
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
            static_collidables_->Retrieve(entity, candidates);
            dynamic_collidables_->Retrieve(entity, candidates);
        }

        for(Rectangle* candidate : candidates)
            candidate->Render(1, 0.5, 0);
    }
}

void Level::AddEntity(Entity* entity) {
    entities_.insert(entity);
    dynamic_collidables_->Insert(entity);
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
