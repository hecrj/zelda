#include "level.hpp"

Level::Level(const char *map) : super(map)
{}

void Level::Update(double delta) {
    // TODO: Remove dead entities

    for(Entity* entity : entities_) {
        entity->Update(delta);

        if(entity->moving())
            collidables_->Update(entity);
    }
}

void Level::Render() {
    super::RenderLayersBelow();

    for(Entity* entity : entities_) {
        entity->Render();
    }

    super::RenderLayersAbove();
}

void Level::AddEntity(Entity* entity) {
    entities_.push_back(entity);
    collidables_->Insert(entity);
}
