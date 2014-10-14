#include "level.hpp"

Level::Level(const char *map) : super(map) {

}

void Level::Update(double delta) {
    // TODO: Remove dead entities

    for(Entity* entity : entities) {
        entity->Update(delta);
    }
}

void Level::Render() {
    super::RenderLayersBelow();

    for(Entity* entity : entities) {
        entity->Render();
    }

    super::RenderLayersAbove();
}

void Level::AddEntity(Entity* entity) {
    entities.push_back(entity);
}
