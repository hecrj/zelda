#include "level.hpp"

Level::Level(const char *map) : super(map) {
    collidables_ = new Quadtree(0, Rectangle(0, 0, map_->width, map_->height));
}

void Level::Update(double delta) {
    // TODO: Remove dead entities

    for(Entity* entity : entities_) {
        entity->Update(delta);
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
