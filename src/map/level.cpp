#include "level.hpp"
#include "../debug.hpp"

Level::Level(const char *map) : super(map)
{}

void Level::Update(double delta) {
    // TODO: Remove dead entities

    for(Entity* entity : entities_) {
        collidables_->Remove(entity);

        entity->Update(delta);

        collidables_->Insert(entity);
        temp_entities_.push_back(entity);
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
        // Show collidable candidates
        std::vector<Rectangle*> candidates;
        collidables_->Retrieve(player_, candidates);

        for(Rectangle* candidate : candidates)
            candidate->Render(1, 0.5, 0);
    }
}

void Level::AddEntity(Entity* entity) {
    entities_.insert(entity);
    collidables_->Insert(entity);
}

void Level::AddCollidable(Rectangle* rectangle) {
    collidables_->Insert(rectangle);
}

void Level::RemoveCollidable(Rectangle* rectangle) {
    collidables_->Remove(rectangle);
}

void Level::set_player(Entity* player) {
    player_ = player;
    AddEntity(player);
}
